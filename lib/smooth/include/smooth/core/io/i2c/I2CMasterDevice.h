//
// Created by permal on 8/19/17.
//

#pragma once

#include <memory>
#include <vector>
#include <mutex>
#include <driver/i2c.h>
#include <driver/gpio.h>
#include <smooth/core/util/FixedBufferBase.h>

namespace smooth
{
    namespace core
    {
        namespace io
        {
            namespace i2c
            {
                /// Base class for all I2C master devices.
                class I2CMasterDevice
                {

                    public:
                        /// Constructor
                        /// \param port The port
                        /// \param address The device address
                        /// \param guard The guard mutex.
                        I2CMasterDevice(i2c_port_t port, uint8_t address, std::mutex& guard)
                                : address(address), port(port), guard(guard)
                        {
                        }

                        virtual ~I2CMasterDevice() = default;

                        /// Scans the bus for devices and reports each found device's address in the provided vector.
                        /// \param found_devices Where the address of found devices are placed
                        void scan_i2c_bus(std::vector<uint8_t>& found_devices) const;

                        std::mutex& get_guard() const
                        {
                            return guard;
                        }

                        /// Determines if a device with the given address is present on the bus.
                        /// \return true if present, otherwise false.
                        bool is_present() const;

                        /// Gets the address of the device
                        /// \return The address
                        uint8_t get_address() const
                        {
                            return address;
                        }

                    protected:
                        /// Writes the data in the vector to the slave with the provided address.
                        /// Usually the data consists of one or more pairs of register and data bytes.
                        /// \param address The slave address.
                        /// \param data The data to write
                        /// \param expect_ack if true, expect ACK from slave.
                        /// \return true on success, false on failure
                        bool write(uint8_t address, std::vector<uint8_t>& data, bool expect_ack = true);

                        /// Reads data from the register of the slave with the provided address.
                        /// \param address The slave address
                        /// \param slave_register The register to read from.
                        /// \param dest Where the data will be written to. The size of the buffer determines how many bytes to read.
                        /// \param use_restart_signal If true, uses a start-condition instead of a stop-condition after the slave address.
                        /// \param end_with_nack If true, ends the transmission with a NACK instead of an ACK.
                        /// \return true on success, false on failure.
                        bool read(uint8_t address,
                                  uint8_t slave_register,
                                  core::util::FixedBufferBase<uint8_t>& dest,
                                  bool use_restart_signal = true,
                                  bool end_with_nack = true);

                        uint8_t address;
                    protected:
                        i2c_port_t port;

                    private:
                        void log_error(esp_err_t err, const char* msg);

                        /// Convert time to ticks
                        /// \param ms Time
                        /// \return Ticks
                        inline TickType_t to_tick(std::chrono::milliseconds ms) const
                        {
                            return pdMS_TO_TICKS(ms.count());
                        }

                        std::mutex& guard;
                };
            }
        }
    }
}