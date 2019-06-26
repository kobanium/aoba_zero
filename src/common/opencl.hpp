// 2019 Team AobaZero
// This source code is in the public domain.
#pragma once
#if defined(USE_OPENCL)
#include <memory>
#include <string>
#include <vector>
#include <cstdint>

namespace OCL {
  using uint = unsigned int;
  class Platform;
  class Platform_impl;
  class Program_impl;
  class Device_impl;
  class Memory_impl;
  class Kernel_impl;
  class Event_impl;
  
  class Event {
    std::unique_ptr<Event_impl> _impl;
  public:
    explicit Event() noexcept;
    ~Event() noexcept;
    Event(Event &&e) noexcept;
    Event &operator=(Event &&event) noexcept;
    Event_impl &get() noexcept;
    const Event_impl &get() const noexcept;
    void wait() const noexcept;
  };

  class Memory {
    std::unique_ptr<Memory_impl> _impl;
  public:
    explicit Memory() noexcept;
    ~Memory() noexcept;
    Memory(Memory_impl &&m_impl) noexcept;
    Memory(Memory &&m) noexcept;
    Memory &operator=(Memory &&m) noexcept;
    Memory_impl &get() noexcept;
    const Memory_impl &get() const noexcept;
    bool ok() const noexcept;
  };

  class Kernel {
    std::unique_ptr<Kernel_impl> _impl;
  public:
    explicit Kernel() noexcept;
    ~Kernel() noexcept;
    Kernel(Kernel_impl &&k_impl) noexcept;
    Kernel(Kernel &&k) noexcept;
    Kernel &operator=(Kernel &&k) noexcept;
    const Kernel_impl &get() const noexcept;
    bool ok() const noexcept;
    void set_arg(uint index, size_t size, const void *value) const noexcept;
    void set_arg(uint index, const Memory &m) const noexcept;
    std::string gen_info() const noexcept;
    size_t gen_work_group_size() const noexcept;
    uint64_t gen_local_mem_size() const noexcept;
    size_t gen_pref_wgs_multiple() const noexcept;
    uint64_t gen_private_mem_size() const noexcept;
  };

  class Program {
    std::unique_ptr<Program_impl> _impl;
  public:
    explicit Program() noexcept;
    ~Program() noexcept;
    Program(Program_impl &&p_impl) noexcept;
    Program(Program &&p) noexcept;
    Program &operator=(Program &&p) noexcept;
    const Program_impl &get() const noexcept;
    bool ok() const noexcept;
    Kernel gen_kernel(const char *name) const noexcept;
  };

  class Device {
    std::unique_ptr<Device_impl> _impl;
  public:
    explicit Device() noexcept;
    ~Device() noexcept;
    Device(Device_impl &&d_impl) noexcept;
    Device(Device &&d) noexcept;
    Device &operator=(Device &&d) noexcept;
    Program gen_program(const char *code);
    Memory gen_mem_r(size_t size) const noexcept;
    Memory gen_mem_w(size_t size) const noexcept;
    Memory gen_mem_rw(size_t size) const noexcept;
    Kernel gen_kernel(const char *name) const noexcept;
    void finish() const noexcept;
    void push_barrier() const noexcept;
    void push_write(const Memory &m, size_t size, const float *p)
      const noexcept;
    void push_read(const Memory &m, size_t size, float *p) const noexcept;
    void push_kernel(const Kernel &k, size_t size_global) const noexcept;
    void enqueue_kernel(const Kernel &k, uint dim, size_t *size_global,
			size_t *size_local) const noexcept;
    bool ok() const noexcept;
    std::string gen_info() const noexcept;
    std::string gen_type() const noexcept;
    std::string gen_local_mem_type() const noexcept;
    std::string gen_name() const noexcept;
    std::string gen_driver_version() const noexcept;
    Platform gen_platform() const noexcept;
    uint gen_max_compute_units() const noexcept;
    size_t gen_max_work_group_size() const noexcept;
    uint gen_max_clock_frequency() const noexcept;
    uint64_t gen_global_mem_size() const noexcept;
    uint64_t gen_max_mem_alloc_size() const noexcept;
    uint64_t gen_local_mem_size() const noexcept;
    size_t gen_kernel_preferred_multiple() const noexcept;
  };
    
  class Platform {
    std::unique_ptr<Platform_impl> _impl;
  public:
    explicit Platform() noexcept;
    ~Platform() noexcept;
    Platform(Platform_impl &&p_impl) noexcept;
    Platform(Platform &&p) noexcept;
    std::vector<Device> gen_devices_all() const noexcept;
    std::string gen_info() const noexcept;
    std::string gen_profile() const noexcept;
    std::string gen_version() const noexcept;
    std::string gen_name() const noexcept;
    std::string gen_extensions() const noexcept;
  };
  std::vector<Platform> gen_platforms() noexcept;
}
#endif
