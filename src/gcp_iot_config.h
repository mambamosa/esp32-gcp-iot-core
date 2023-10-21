// This file contains your configuration used to connect to Google Cloud IoT Core.

// WiFi network credentials
const char *ssid = "SSID";
const char *password = "PASSWORD";

// Google Cloud IoT Core credentials
const char *project_id = "project-id";
const char *location = "asia-east1";
const char *registry_id = "my-registry";
const char *device_id = "my-esp32-device";

// NTP configuration
const char* ntp_primary = "pool.ntp.org";
const char* ntp_secondary = "time.nist.gov";

const char *private_key_str =
    "6e:b8:17:35:c7:fc:6b:d7:a9:cb:cb:49:7f:a0:67:"
    "63:38:b0:90:57:57:e0:c0:9a:e8:6f:06:0c:d9:ee:"
    "31:41";

// Time in seconds to expire token += 20 minute for drift. Max is 24 hours (3600 * 24)
const int jwt_exp_secs = 60*20;

const char *root_cert =
    "-----BEGIN CERTIFICATE-----\n"
    "Generate Eliptic Curve (EC) private/public key pair\n"
    "Extract Eliptic Curve (EC) private key\n"
    "Copy and paste it in this part of the code\n"
    "-----END CERTIFICATE-----\n";