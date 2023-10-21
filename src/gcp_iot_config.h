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
    "Generate Eliptic Curve (EC) private/public key pair"
    "Extract Eliptic Curve (EC) private key"
    "Copy and paste it in this part of the code";

// Time in seconds to expire token += 20 minute for drift. Max is 24 hours (3600 * 24)
const int jwt_exp_secs = 60*20;

const char *root_cert =
    "-----BEGIN CERTIFICATE-----\n"
    "Paste the certificate bytes from root certificate of Google here.\n"
    "You can use any of the root certificate bytes with Google Trust Services (GTS)\n"
    "as the Certificate Authority (CA)\n"
    "-----END CERTIFICATE-----\n";