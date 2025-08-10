# WiFiSetupManager Library for ESP8266

🛜 WiFi configuration manager with captive portal for ESP8266. Provides AP mode with web interface for easy WiFi setup. Supports both blocking and non-blocking operation modes. Stores credentials for automatic reconnection. Perfect for IoT devices requiring first-time setup.

## Features

- 🛠️ Built-in captive portal with DNS redirection
- 📶 Seamless switching between AP and STA modes
- 🔒 Secure string handling (no `String` objects)
- 📱 Mobile-friendly configuration page
- ⏳ Both blocking and non-blocking operation modes

## Installation

### Install from Arduino Library Manager (recommended)

1. Open **Arduino IDE**
2. Go to **Sketch** → **Include Library** → **Manage Libraries...**
3. Search for `ESP8266-WiFiSetupManager`
4. Click **Install**
5. Restart Arduino IDE

### Manual Installation

#### Option A - Using Git:

```bash
    cd ~/Documents/Arduino/libraries/ # Default libraries location
    git clone https://github.com/yourusername/ESP8266-WiFiSetupManager.git
```

#### Option B - Download ZIP:

   - Download the repository as ZIP
   - In Arduino IDE: **Sketch** → **Include Library** → **Add .ZIP Library...**
   - Select the downloaded ZIP file 3. Restart Arduino IDE to refresh the library list 4. **Option B - Download ZIP**:

#### Option C - Using arduino-cli

```bash
  # Install the library directly from GitHub
arduino-cli lib install --git-url https://github.com/BorisKotlyarov/ESP8266-WiFiSetupManager.git

    # Or install from a ZIP file (after downloading)
arduino-cli lib install --zip-path /path/to/ESP8266-WiFiSetupManager.zip
```

6. Restart Arduino IDE to refresh the library list

### Verify Installation

After installation, check that examples are available in:  
**File** → **Examples** → **ESP8266-WiFiSetupManager** →

- `BasicConfig`
- `NonBlocking`

## Basic Usage

### 1. Blocking Mode (Simple Setup)

```cpp
#include <WiFiSetupManager.h>

WiFiSetupManager wifiSetup("MyDevice");

void setup() {
  Serial.begin(115200);
  wifiSetup.runBlocking(); // Stops here until configured

  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("Connected to %s!\n", WiFi.SSID().c_str());
  }
}

void loop() {}
```

### 2. Non-Blocking Mode (Advanced)

```cpp
#include <WiFiSetupManager.h>

WiFiSetupManager wifiSetup("MyDevice");

void setup() {
  Serial.begin(115200);
  wifiSetup.begin();
}

void loop() {
  if (wifiSetup.process()) { // Returns true when configured
    auto& config = wifiSetup.getConfig();
    Serial.printf("Got new config: %s/%s\n", config.SSID, config.password);
  }

  // Your other code here
  digitalWrite(LED_BUILTIN, millis() % 1000 < 500);
}
```

## API Reference

### Constructor

```cpp
WiFiSetupManager(
  const char* apName = "ESP8266-AP",
  IPAddress apIP = IPAddress(192, 168, 1, 1),
  IPAddress subnet = IPAddress(255, 255, 255, 0)
)
```

### Core Methods

| Method               | Description                              |
| -------------------- | ---------------------------------------- |
| `void begin()`       | Starts AP and web server                 |
| `void stop()`        | Stops AP and cleans up                   |
| `bool process()`     | Handles client requests (call in loop()) |
| `void runBlocking()` | Runs until WiFi is configured            |

### Configuration Access

```cpp
struct Config {
  char SSID[32];
  char password[64];
  uint8_t mode;
};

const Config& getConfig() const;
```

### Status Codes

| Code | Meaning              |
| ---- | -------------------- |
| 0    | Portal running       |
| 1    | Credentials received |
| 4    | User exited portal   |

## Advanced Examples

### Persistent Configuration

Add EEPROM saving:

```cpp
#include <EEPROM.h>

void saveConfig(const char* ssid, const char* pass) {
  EEPROM.begin(512);
  // Your saving logic here
  EEPROM.end();
}

wifiSetup.runBlocking();
saveConfig(wifiSetup.getConfig().SSID,
           wifiSetup.getConfig().password);
```

## Troubleshooting

**Q: Portal doesn't appear on my phone**

- Ensure you're connecting to the correct AP
- Try manually navigating to `192.168.1.1`

**Q: Connection keeps failing**

- Verify your router's password requirements
- Check serial monitor for error messages

## License

MIT License. See [LICENSE](LICENSE) file.
