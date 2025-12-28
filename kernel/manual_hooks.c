// Manual hooks compatibility layer for SukiSU Ultra
#include <linux/export.h>
#include <linux/fs.h>
#include <linux/types.h>

// Hook enable flags
bool ksu_execveat_hook __read_mostly = true;
bool ksu_vfs_read_hook __read_mostly = true;
bool ksu_input_hook __read_mostly = true;
bool ksu_devpts_hook __read_mostly = true;

EXPORT_SYMBOL(ksu_execveat_hook);
EXPORT_SYMBOL(ksu_vfs_read_hook);
EXPORT_SYMBOL(ksu_input_hook);
EXPORT_SYMBOL(ksu_devpts_hook);

// Forward declarations from other files
extern int ksu_handle_execveat_ksud(int *fd, struct filename **filename_ptr,
                                    void *argv, void *envp, int *flags);
extern int ksu_handle_execve_sucompat(const char __user **filename_user,
                                      void *argv, void *envp);
extern int ksu_handle_vfs_read(unsigned int fd, char __user **buf_ptr,
                               size_t *count_ptr);
extern int ksu_handle_input_handle_event(unsigned int *type, unsigned int *code,
                                         int *value);
extern int ksu_handle_faccessat(int *dfd, const char __user **filename_user,
                                int *mode, int *flags);
extern int ksu_handle_stat(int *dfd, const char __user **filename_user,
                           int *flags);

// Wrapper for devpts - SukiSU doesn't have this, make it no-op
int ksu_handle_devpts(struct inode *inode) {
    return 0;
}

EXPORT_SYMBOL(ksu_handle_execveat_ksud);
EXPORT_SYMBOL(ksu_handle_execve_sucompat);
EXPORT_SYMBOL(ksu_handle_vfs_read);
EXPORT_SYMBOL(ksu_handle_input_handle_event);
EXPORT_SYMBOL(ksu_handle_faccessat);
EXPORT_SYMBOL(ksu_handle_stat);
EXPORT_SYMBOL(ksu_handle_devpts);
