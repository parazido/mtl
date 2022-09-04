#pragma once

#include <devices/common.hpp>
#include <devices/devices.hpp>
#include "sys.hpp"


extern "C" uint32_t isr_table_address;


namespace mcu::specific {
	namespace detail {
		class interrupts {
		public:
			__attribute__((naked))
			inline static void enable() noexcept {
				__asm volatile ("cpsie	i");
			}
		
			template<class t_interrupt>
			inline static void enable() noexcept {
				t_interrupt::set_enable_register::set(1 << ((t_interrupt::offset - 16) % 32));
			}
			
			__attribute__((naked))
			inline static void disable() noexcept {
				__asm volatile ("cpsid	i");
			}
			
			template<class t_interrupt>
			inline static void disable() noexcept {
				t_interrupt::clear_enable_register::set(1 << ((t_interrupt::offset - 16) % 32));
			}
			
			template<class t_interrupt>
			inline static void set() noexcept {
				t_interrupt::set_pending_register::set(1 << ((t_interrupt::offset - 16) % 32));
			}
			
			template<class t_interrupt>
			inline static void clear() noexcept {
				t_interrupt::clear_pending_register::set(1 << ((t_interrupt::offset - 16) % 32));
			}
			
			template<class t_interrupt>
			inline static bool active() noexcept {
				return t_interrupt::active_register::test(1 << ((t_interrupt::offset - 16) % 32));
			}
			
			template<class t_interrupt, class t_handler>
			inline static void set_handler(t_handler handler) noexcept {
				ram_interrupt_table[t_interrupt::offset] = reinterpret_cast<uint32_t>(handler);
			}
			
			static void remap() noexcept {
				// Temporary replaced with the copying of initial values (for debugging purposes).
				// for (auto &entry : ram_interrupt_table) {
				//	entry = reinterpret_cast<uint32_t>(&default_handler);
				// }
				auto source_table = reinterpret_cast<uint32_t *>(0);
				for (int i = 0; i < sizeof(ram_interrupt_table) / sizeof(ram_interrupt_table[0]); ++i) {
					ram_interrupt_table[i] = source_table[i];
				}
				
				// Set new table pointer.
				mtl::hw::nvic::csb
				isr_table_address = reinterpret_cast<uint32_t>(ram_interrupt_table);
			}
		
		private:
			alignas(128 * sizeof(uint32_t)) // Number of interrupts rounded to the upper power of 2 value.
			inline static uint32_t ram_interrupt_table[73];
			
			// Default interrupt handler.
			__attribute__((naked))
			inline static void default_handler() {
				__asm volatile ("b	.");
			}
		};
		
		
		class services {
		public:
			static void initialize() noexcept {
				// Setup handler, clear and activate SVC interrupt.
				interrupts::set_handler<devices::interrupts::svc>(handler);
				//interrupts::clear<devices::interrupts::svc>();
				//interrupts::enable<devices::interrupts::svc>();
			}
		
			inline static void start_os() noexcept __attribute__((naked)) {
				asm volatile (
					"svc	0\n"
				);
			}

			template<class t_service, class... t_parameters>
			static void call_os_service(t_parameters&&... parameters) noexcept __attribute__((naked)) {
				asm volatile (
					"push	{r0}\n"
				);
				asm volatile (
					//"mov	r0, %[entry]\n"
					"push	{r0}\n"
					"ldr	r0, [sp, #4]\n"
					"svc	1\n"
					"add	sp, #8\n"
					"bx		lr\n"
					: : [entry] "r" (reinterpret_cast<uint32_t>(t_service::entry)) : "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "memory", "cc"
				);
			}
	
			inline static void set_start_os_handler(void(*handler)()) noexcept {
				m_entries[0] = reinterpret_cast<uint32_t>(handler);
			}

			inline static void set_os_service_handler(void(*handler)()) noexcept {
				m_entries[1] = reinterpret_cast<uint32_t>(handler);
			}
			
		private:			
			__attribute__((naked))
			static void handler() noexcept {
				asm volatile (
					"tst		lr, #4\n"
					"ite		eq\n"
					"mrseq		r3, msp\n"
					"mrsne		r3, psp\n"
					"ldr		r0, [r3, #24]\n"
					"ldrb		r0, [r0, #-2]\n"
					"mov		r0, r0, asl #2\n"
					"mov		r1, %[entries]\n"
					"ldr		r1, [r1, r0]\n"
					"bx			r1\n"
					: : [entries] "r" (reinterpret_cast<uint32_t>(&m_entries)) : "r0", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "memory", "cc"
				);
			}
			
			static void os_service_default_handler() noexcept {}

			inline static uint32_t m_entries[2];
		};
	}
	
	class sys_t {
	public:
		using interrupts = detail::interrupts;
		using services = detail::services;
	
		// This method should be called before main() method.
		inline static void startup() noexcept {
			// Configure flash memory for high speed operation.
			devices::flash::acr::prftbe::set(devices::flash::acr::prftbe::enabled);
			devices::flash::acr::latency::set(devices::flash::acr::latency::one);
			while (!devices::flash::acr::latency::test(devices::flash::acr::latency::one));
		
			// Setup clocks for appropriate frequency.
			// Turn HSI on.
			devices::rcc::cr::hsion::set(devices::rcc::cr::hsion::on);
			while (!(devices::rcc::cr::hsirdy::test(devices::rcc::cr::hsirdy::ready)));
			
			// Configure PLL.
			devices::rcc::cfgr::pllmul::set(devices::rcc::cfgr::pllmul::mul8);
			// Turn PLL on.
			devices::rcc::cr::pllon::set(devices::rcc::cr::pllon::on);
			while (!(devices::rcc::cr::pllrdy::test(devices::rcc::cr::pllrdy::ready)));
			
			// Use PLL as a source for clocking.
			devices::rcc::cfgr::sw::set(devices::rcc::cfgr::sw::pll);
			
			// // Divide APB1 by 16.
			// devices::rcc::cfgr::ppre1::set(devices::rcc::cfgr::ppre1::by16);
		}
		
		inline static void initialize() noexcept {
			// Remap interrupt table.
			detail::interrupts::remap();
			// Initialize system services.
			detail::services::initialize();
			// Allow interrupts.
			detail::interrupts::enable();
		}
		
		
		inline static uint32_t initial_stack_pointer() noexcept {
			// Temporary replaced.
			// __asm volatile ("ldr	r0, =__initial_sp");
			// __asm volatile ("bx		lr");
			return reinterpret_cast<uint32_t *>(0)[0];
		}		
	};
}
