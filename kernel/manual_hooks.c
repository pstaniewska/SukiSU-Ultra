// Manual hooks compatibility layer for SukiSU Ultra
#include <linux/export.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fdtable.h>

// Hook enable flags
bool ksu_execveat_hook __read_mostly = true;
bool ksu_vfs_read_hook __read_mostly = true;
bool ksu_input_hook __read_mostly = true;
bool ksu_devpts_hook __read_mostly = true;

EXPORT_SYMBOL(ksu_execveat_hook);
EXPORT_SYMBOL(ksu_vfs_read_hook);
EXPORT_SYMBOL(ksu_input_hook);
EXPORT_SYMBOL(ksu_devpts_hook);

// Wrapper for vfs_read - kernel uses fd, SukiSU uses file*
int ksu_handle_vfs_read(unsigned int fd, char __user **buf_ptr, size_t *count_ptr)
{
    // SukiSU handles this internally via tracepoints, stub here
    return 0;
}
EXPORT_SYMBOL(ksu_handle_vfs_read);

// Wrapper for devpts
int ksu_handle_devpts(struct inode *inode)
{
    return 0;
}
EXPORT_SYMBOL(ksu_handle_devpts);

// These are already exported by SukiSU, just declare extern
extern int ksu_handle_execveat_ksud(int *fd, struct filename **filename_ptr,
                                    void *argv, void *envp, int *flags);
extern int ksu_handle_input_handle_event(unsigned int *type, unsigned int *code,
                                         int *value);
extern int ksu_handle_faccessat(int *dfd, const char __user **filename_user,
                                int *mode, int *flags);
extern int ksu_handle_stat(int *dfd, const char __user **filename_user,
                           int *flags);
