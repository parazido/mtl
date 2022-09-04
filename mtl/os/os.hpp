#pragma once

#include <new>
#include <type_traits>

#include <mtl/hw/adc.hpp>
#include <mtl/hw/dma.hpp>
#include <mtl/hw/nvic.hpp>
#include <mtl/hw/timer.hpp>
#include <mtl/hw/usart.hpp>
#include <mtl/os/api.hpp>
#include <mtl/os/context.hpp>
#include <mtl/os/event.hpp>
#include <mtl/os/isr.hpp>
#include <mtl/os/routine.hpp>
#include <mtl/os/task.hpp>
#include <mtl/sys/sys.hpp>

namespace mtl {
    namespace os_ {
        template <class t_task> struct idle_task { using task = t_task; };
    } // namespace os_

    namespace detail {
        // Default task.
        class default_idle_task {
        public:
            void entry() {
                for (;;) {
                    ;
                }
            }

            using routines = mtl::routines<mtl::routine<&default_idle_task::entry>>;
        };

        // Extract routines from tasks.
        template <class...> struct tasks_to_routines {
            using next = void;
            using type = void;
            constexpr static size_t size = 0;
        };

        template <class t_first, class... t_rest> struct tasks_to_routines<t_first, t_rest...> {};

        template <class t_last> struct tasks_to_routines<t_last> {};

        // OS data.
        struct routine_descriptor {
            uint8_t flags;
            uint8_t routine_id;
            uint32_t stack_pointer;
        };

        template <class...> struct number_of_routines;

        template <class t_tasks> struct number_of_routines<t_tasks> {
            constexpr static uint8_t value
                = number_of_routines<typename t_tasks::next>::value + t_tasks::task_type::routines::size;
        };

        template <> struct number_of_routines<tasks<>> { constexpr static uint8_t value = 0; };

        template <class t_tasks> class os_data {
        public:
            os_data() = default;

            // private:
        public:
            using tasks = t_tasks;
            constexpr static size_t number_of_tasks = tasks::size;
            constexpr static size_t number_of_routines = number_of_routines<tasks>::value;

            uint8_t m_current_routine;
            uint8_t m_active_routines;
            uint32_t m_stack;
            routine_descriptor m_routine_descriptors[number_of_routines];
            tasks m_tasks;

            template <class...> friend class os;
        };

        // Task concatenator.
        template <class...> struct concat_tasks;

        template <class... t_left, class... t_right> struct concat_tasks<tasks<t_left...>, tasks<t_right...>> {
            using type = tasks<t_left..., t_right...>;
        };
    } // namespace detail

    template <class... t_parameters> class os {
    public:
        using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
        static_assert(!std::is_same<sys, void>::value, "sys must not be void");
        using idle_task =
            typename mtl::parameters<t_parameters...>::find_type<os_::idle_task, detail::default_idle_task>::type;
        static_assert(std::is_same<idle_task, detail::default_idle_task>::value, "idle_task must not be void");
        using tasks =
            typename detail::concat_tasks<mtl::tasks<mtl::task<idle_task>>,
                                          typename mtl::parameters<t_parameters...>::find_type<mtl::tasks>::type>::type;
        using os_data = detail::os_data<tasks>;

        // static void start_application() {
        //     // Setup USART1.
        //     using usart1 = mtl::hw::usart1;
        //     usart1::cr2::write(usart1::cr2::stop::bits1);
        //     usart1::cr3::write(usart1::cr3::dmat::enabled);
        //     usart1::brr::write(0x22c);
        //     usart1::gtpr::write(0);
        //     usart1::cr1::write(usart1::cr1::ue::enabled, usart1::cr1::te::enabled);

        //     // ADC.
        //     using adc = mtl::hw::adc;
        //     adc::ier::write(0);
        //     adc::cfgr1::write(adc::cfgr1::discen::enabled, adc::cfgr1::exten::rising, adc::cfgr1::extsel::trg1,
        //                       adc::cfgr1::res::bits8, adc::cfgr1::dmacfg::circular, adc::cfgr1::dmaen::enabled);
        //     adc::cfgr2::write(adc::cfgr2::ckmode:adcclk);
        //     adc::smpr::write(adc::smpr::smp::clocks13_5);
        //     adc::chselr::write(1 << 6);

        //     // PB0 - brake.
        //     // PA6 - throttle.

        //     adc::cr::write(adc::cr::aden::enabled);
        // }

        static void run() {
            // Configure basic environment (clocks, interrupt handlers, etc.).
            // It will be better to run this part before main() method, because C++ auxiliary hidden code can be
            // executed on unconfigured hardware (for example low frequency, etc.).
            sys::initialize();

            sys::services::set_start_os_handler(&start_mt_mode_service);
            sys::services::set_os_service_handler(&call_service);

            // Initialize api/isr.
            mtl::api::register_entries(&wait, &set);
            mtl::isr::register_entries(&set_from_isr);

            // Initialize OS data.
            auto *x = new (m_os_data_storage) os_data();

            // Initialize tasks.
            initialize_tasks<0>(get_os_data().m_tasks);

            // Go into multitask mode.
            sys::services::start_os();
        }

    private:
        static void initialize_routine(detail::routine_descriptor &routine_descriptor, void *stack,
                                       void *object_pointer, void *entry_pointer) {
            // Initialize stack.
            context::hardware_stack_frame *hw_stack_frame = reinterpret_cast<context::hardware_stack_frame *>(
                reinterpret_cast<uint32_t>(stack) - context::hardware_stack_frame_size);
            hw_stack_frame->r0 = reinterpret_cast<uint32_t>(object_pointer);
            hw_stack_frame->r1 = 1;
            hw_stack_frame->r2 = 2;
            hw_stack_frame->r3 = 3;
            hw_stack_frame->pc = reinterpret_cast<uint32_t>(entry_pointer);
            hw_stack_frame->psr = 0x21000000;
            routine_descriptor.flags = static_cast<uint8_t>(routine_state::active);
            routine_descriptor.stack_pointer = reinterpret_cast<uint32_t>(stack) - context::stack_frame_size;
            auto *ssf = reinterpret_cast<context::software_stack_frame *>(reinterpret_cast<uint32_t>(stack)
                                                                          - context::stack_frame_size);
            ssf->r4 = 4;
            ssf->r5 = 5;
            ssf->r6 = 6;
            ssf->r7 = 7;
            ssf->r8 = 8;
            ssf->r9 = 9;
            ssf->r10 = 10;
            ssf->r11 = 11;
        }

        template <uint8_t v_routine_counter, class t_tasks> static void initialize_tasks(t_tasks &tasks) {
            using task = typename t_tasks::task_type;
            initialize_routines<v_routine_counter>(tasks.task, tasks.task.m_routines);
            if constexpr (t_tasks::size > 1) {
                initialize_tasks<v_routine_counter + task::routines::size>(tasks.next_tasks);
            }
        };

        template <uint8_t v_routine_counter, class t_task, class t_routines>
        static void initialize_routines(t_task &task, t_routines &routines) {
            using routine = typename t_routines::type;
            initialize_routine(get_os_data().m_routine_descriptors[v_routine_counter],
                               reinterpret_cast<uint8_t *>(&routines.routine.m_stack)
                                   + sizeof(routines.routine.m_stack),
                               &task.m_task, reinterpret_cast<void *>(&t_routines::type::call));
            if constexpr (t_routines::size > 1) {
                initialize_routines<v_routine_counter + 1>(task, routines.next_routines);
            }
        };

        static uint32_t switch_context() {
            auto &os_data_storage = get_os_data();

            // If no active routines available, just return back to the idle one.
            if (os_data_storage.m_active_routines == 0) {
                os_data_storage.m_current_routine = 0;
            }

            // If one active routine available, just return back to the current one.
            if (os_data_storage.m_active_routines < 2) {
                return os_data_storage.m_routine_descriptors[os_data_storage.m_current_routine].stack_pointer;
            }

            // Looking for the next routine.
            auto start_index = os_data_storage.m_current_routine;
            auto current_index = start_index;
            for (;;) {
                // Get next routine index and.
                ++current_index;
                if (current_index >= os_data_storage.number_of_routines) {
                    current_index = 1;
                }
                // Check if routine is waiting for an execution slot.
                if (os_data_storage.m_routine_descriptors[current_index].flags
                    & static_cast<uint8_t>(routine_state::active)) {
                    os_data_storage.m_current_routine = current_index;
                    return os_data_storage.m_routine_descriptors[current_index].stack_pointer;
                }
            }
        }

        static void initialize_timer() noexcept {
            // Initialize interrupt handler.
            sys::interrupts::template set_handler<mtl::hw::interrupts::sys_tick>(&systick_handler);
            // sys::interrupts::clear<devices::interrupts::sys_tick>();
            // sys::interrupts::enable<devices::interrupts::sys_tick>();

            // Initialize system timer.
            mtl::hw::nvic::strvr::write(9000);
            mtl::hw::nvic::stcvr::write(0);
            mtl::hw::nvic::stcsr::write(3);
        }

        static void systick_handler() noexcept {
            using nvic = mtl::hw::nvic;
            // constexpr uint32_t thread_return = 0xfffffffd;

            auto &os_data_storage = get_os_data();
            context::save();
            // os_data_storage.m_stack = context::read_system_stack_pointer();
            if (nvic::stcsr::countflag::get() == static_cast<uint32_t>(nvic::stcsr::countflag::active)) {
                os_data_storage.m_routine_descriptors[os_data_storage.m_current_routine].stack_pointer
                    = context::read_routine_stack_pointer();
                switch_context();
                // *reinterpret_cast<uint32_t *>(os_data_storage.m_stack) = thread_return;
                context::write_routine_stack_pointer(
                    os_data_storage.m_routine_descriptors[os_data_storage.m_current_routine].stack_pointer);
            }
            context::load();
        }

        static void pendsv_handler() {
            context::save();
            get_os_data().m_stack = context::read_system_stack_pointer();
            switch_context();
            context::load();
        }

        alignas(sizeof(uint32_t)) inline static uint8_t m_os_data_storage[sizeof(os_data)];

        inline static os_data &get_os_data() { return *reinterpret_cast<os_data *>(m_os_data_storage); }

        static void start_mt_mode_service() noexcept {
            auto &os_data_storage = get_os_data();
            initialize_timer();
            os_data_storage.m_current_routine = 1;
            os_data_storage.m_active_routines = os_data_storage.number_of_routines - 1;
            // os_data_storage.m_stack = context::read_system_stack_pointer() + 24;
            //*reinterpret_cast<uint32_t *>(os_data_storage.m_stack) = thread_return;
            context::write_routine_stack_pointer(
                os_data_storage.m_routine_descriptors[os_data_storage.m_current_routine].stack_pointer);
            context::load();
            asm volatile("ldr	r0, =0xfffffffd\n"
                         "mov	lr, r0\n"
                         "bx		lr\n");
        }

        static void call_service() noexcept __attribute__((naked)) {
            asm volatile("mrs		r0, psp\n"
                         "sub		r0, #16\n"
                         "stmia	r0!, {r4-r7}\n"
                         "mov		r4, r8\n"
                         "mov		r5, r9\n"
                         "mov		r6, r10\n"
                         "mov		r7, r11\n"
                         "sub		r0, #32\n"
                         "stmia	r0!, {r4-r7}\n"
                         "sub		r0, #16\n"
                         "msr		 psp, r0\n"
                         "mov		r0, lr\n"
                         "push		{r0}\n"
                         "mrs		r3, psp\n"
                         "ldr		r4, [r3, #0x44]\n"
                         "ldr		r0, [r3, #0x20]\n"
                         "ldr		r1, [r3, #0x24]\n"
                         "ldr		r2, [r3, #0x28]\n"
                         "ldr		r3, [r3, #0x2c]\n"
                         "blx		r4\n"
                         "pop		{r0}\n"
                         "mov		lr, r0\n"
                         "mrs 		r0, psp\n"
                         "ldmia	r0!, {r4-r7}\n"
                         "mov		r8, r4\n"
                         "mov		r9, r5\n"
                         "mov		r10, r6\n"
                         "mov		r11, r7\n"
                         "ldmia	r0!, {r4-r7}\n"
                         "msr		psp, r0\n"
                         "bx			lr\n");
        }

        template <auto v_entry> struct service_t { constexpr static auto entry = v_entry; };

        // Wait service.
        static inline void wait_service(mtl::event &e) {
            if (!e.m_flag) {
                suspend_routine_service();
            }
        }

        using svc_wait = service_t<&wait_service>;

        static inline void wait(mtl::event &e) {
            auto &os_data_storage = get_os_data();
            e.m_routine = os_data_storage.m_current_routine;
            sys::services::template call_os_service<svc_wait>(e);
            e.m_flag = false;
        }

        // Set service.
        static inline void set_service(mtl::event &e) {
            e.m_flag = true;
            wakeup_routine_service(e.m_routine);
        }

        static inline void set_from_isr(mtl::event &e) {
            e.m_flag = true;
            wakeup_routine_service(e.m_routine);
        }

        using svc_set = service_t<&set_service>;

        static inline void set(mtl::event &e) { sys::services::template call_os_service<svc_set>(e); }

        // Suspend service.
        static void suspend_routine_service() noexcept {
            auto &os_data_storage = get_os_data();
            if (os_data_storage.m_routine_descriptors[os_data_storage.m_current_routine].flags
                & static_cast<uint8_t>(routine_state::active)) {
                --os_data_storage.m_active_routines;
                os_data_storage.m_routine_descriptors[os_data_storage.m_current_routine].flags
                    ^= static_cast<uint8_t>(routine_state::active) | static_cast<uint8_t>(routine_state::suspended);
            }
            os_data_storage.m_routine_descriptors[os_data_storage.m_current_routine].stack_pointer
                = context::read_routine_stack_pointer();
            switch_context();
            context::write_routine_stack_pointer(
                os_data_storage.m_routine_descriptors[os_data_storage.m_current_routine].stack_pointer);
        }

        // Wakeup service.
        static void wakeup_routine_service(uint8_t index) {
            auto &os_data_storage = get_os_data();
            if (!(os_data_storage.m_routine_descriptors[index].flags & static_cast<uint8_t>(routine_state::active))) {
                ++os_data_storage.m_active_routines;
                os_data_storage.m_routine_descriptors[index].flags
                    ^= static_cast<uint8_t>(routine_state::active) | static_cast<uint8_t>(routine_state::suspended);
            }
        }
    };
} // namespace mtl
