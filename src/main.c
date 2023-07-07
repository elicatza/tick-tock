#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <proc/readproc.h>

#define LIBNOTIFY_DISABLE_DEPRECATED
#include <libnotify/notify.h>


#define ICON "/usr/share/icons/Adwaita/96x96/status/alarm-symbolic.symbolic.png"

gboolean is_readable(char *path)
{
    if (access(path, R_OK)) return 1;
    return 0;
}

long get_uptime(void)
{
    char* uptime_path = "/proc/uptime";

    // Open file
    FILE *fd = fopen(uptime_path, "r");
    if (fd == NULL) {
        fprintf(stderr, "ERROR: unable to open `%s`\n", uptime_path);
        exit(1);
    }

    long rt;
    if (fscanf(fd, "%ld", &rt) == EOF) {
        fprintf(stderr, "ERROR: unable to parse `%s`: %s\n", uptime_path, strerror(errno));
        exit(1);
    }

    fclose(fd);
    return rt;
}

// Extract field from string list seperated by d
void cut(char d, size_t field, char* buffer, size_t buffsz, FILE *fd)
{
    size_t field_counter = 0;
    char ch;
    while ((ch = fgetc(fd)) != EOF) {
        if (ch == d) {
            ++field_counter;
            if (field_counter == field - 1) {
                fgets(buffer, buffsz, fd);
            }
        }
    }
}

long get_proc_start_ms(char *name, size_t *instances)
{
    PROCTAB *proc = openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS);
    proc_t proc_buff;
    long rt;
    memset(&proc_buff, 0, sizeof(proc_buff));  // readproc documentation says it has to be initialized to 0

    while (readproc(proc, &proc_buff)) {
        if (strcmp(proc_buff.cmd, name) != 0) continue;
        ++*instances;

        if (*instances == 1) {
            rt = proc_buff.start_time;
        }
    }
    return rt;
}

#define NOTIFY_DISPLAY(note) assert(notify_notification_show((note), NULL))


int main(void)
{
    notify_init("tick-tock");

    char *icon = ICON;
    if (!is_readable(ICON)) icon = NULL;

    size_t instances = 0;
    long time_diff = get_uptime() - (get_proc_start_ms("tick-tock", &instances) / 100);

    // notify user and exit if program is already running
    if (instances != 1) {
        char msg[32];
        long minutes = time_diff / 60;
        snprintf(msg, sizeof msg, "Uptime: %02ld:%02ld", minutes, time_diff - (minutes * 60));

        NotifyNotification *note = notify_notification_new("Tick-Tock Running", msg, icon);
        notify_notification_set_timeout(note, 3000);
        NOTIFY_DISPLAY(note);
        return 0;
    }

    NotifyNotification *note = notify_notification_new("Tick-Tock Started", NULL, icon);
    notify_notification_set_timeout(note, 3000);
    NOTIFY_DISPLAY(note);


    notify_notification_set_urgency(note, NOTIFY_URGENCY_CRITICAL);
    NotifyNotification *end_note = notify_notification_new("Tick-Tock Done", NULL, icon);
    notify_notification_set_timeout(end_note, 10 * 1000);
    sleep(60 * 45);

    NOTIFY_DISPLAY(end_note);

    return 0;
}
