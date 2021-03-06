//
// Created by permal on 6/24/17.
//

#pragma once

#include <string>
#include <array>
#include <esp_wifi.h>
#include <smooth/core/ipc/IEventListener.h>

namespace smooth
{
    namespace core
    {
        namespace network
        {
            /// Wifi management class
            class Wifi
                    : public smooth::core::ipc::IEventListener<system_event_t>
            {
                public:
                    Wifi();
                    Wifi(const Wifi&) = delete;
                    virtual ~Wifi();

                    /// Sets the hostname
                    /// \param name The name
                    void set_host_name(const std::string& name);
                    /// Sets the credentials for the Wifi network
                    /// \param ssid The SSID
                    /// \param password The password
                    void set_ap_credentials(const std::string& ssid, const std::string& password);
                    /// Enables, disables auto reconnect on loss of Wifi connection.
                    /// \param auto_connect
                    void set_auto_connect(bool auto_connect);

                    /// Initiates the connection to the AP.
                    void connect_to_ap();

                    /// Returns a value indicating of currently connected to the access point.
                    /// \return
                    bool is_connected_to_ap() const;

                    /// Returns a value indicating if the required settings are set.
                    /// \return true or false.
                    bool is_configured() const
                    {
                        return host_name.length() > 0 && ssid.length() > 0 && password.length() > 0;
                    }

                    /// Event response method
                    /// \param event The event
                    void event(const system_event_t& event) override;

                    std::string get_mac_address();

                private:
                    void connect();
                    bool auto_connect_to_ap = false;
                    bool connected_to_ap = false;
                    std::string host_name = "Smooth-Wifi";
                    std::string ssid;
                    std::string password;
            };
        }
    }
}