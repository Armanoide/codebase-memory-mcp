/*
 * config.h — Persistent UI configuration.
 *
 * Stores ui_enabled and ui_port in ~/.cache/codebase-memory-mcp/config.json.
 * Thread-safe: load/save are independent operations on the filesystem.
 */
#ifndef CBM_UI_CONFIG_H
#define CBM_UI_CONFIG_H

#include <stdbool.h>

/* Default values */
#define CBM_UI_DEFAULT_PORT 9749
#define CBM_UI_DEFAULT_ENABLED false
/* Fork patch (feat/ui-host): default bind stays loopback; set ui_host to
 * 0.0.0.0 (or a specific LAN IPv4) to expose the UI on a trusted network. */
#define CBM_UI_DEFAULT_HOST "127.0.0.1"
#define CBM_UI_HOST_MAX 64

typedef struct {
    bool ui_enabled;
    int ui_port;
    char ui_host[CBM_UI_HOST_MAX];
} cbm_ui_config_t;

/* Validate an IPv4 dotted-quad literal (no hostnames). */
bool cbm_ui_host_is_valid(const char *host);

/* True when host is an IPv4 in 127.0.0.0/8. */
bool cbm_ui_host_is_loopback(const char *host);

/* Load config from disk. Missing/corrupt file → defaults. */
void cbm_ui_config_load(cbm_ui_config_t *cfg);

/* Atomically save one complete config generation. Creates the directory if
 * needed and reports write/sync/replace failures. */
bool cbm_ui_config_save(const cbm_ui_config_t *cfg);

/* Get the config file path. Writes to buf (up to bufsz bytes).
 * Exposed for testing. */
void cbm_ui_config_path(char *buf, int bufsz);

#endif /* CBM_UI_CONFIG_H */
