// Manual hooks compatibility layer for SukiSU Ultra
// Provides stub functions for kernel patches that call KSU manual hooks
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

// Stub for sys_read hook - kernel calls this from read_write.c
int ksu_handle_sys_read(unsigned int fd, char __user **buf_ptr, size_t *count_ptr)
{
    return 0;
}
EXPORT_SYMBOL(ksu_handle_sys_read);

// Stub for vfs_read hook (alternative name)
int ksu_handle_vfs_read(unsigned int fd, char __user **buf_ptr, size_t *count_ptr)
{
    return 0;
}
EXPORT_SYMBOL(ksu_handle_vfs_read);

// Stub for execveat hook - kernel calls this from exec.c
int ksu_handle_execveat(int *fd, struct filename **filename_ptr,
                        void *argv, void *envp, int *flags)
{
    return 0;
}
EXPORT_SYMBOL(ksu_handle_execveat);

// Stub for execveat sucompat hook - kernel calls this from exec.c
int ksu_handle_execveat_sucompat(int *fd, struct filename **filename_ptr,
                                 void *argv, void *envp, int *flags)
{
    return 0;
}
EXPORT_SYMBOL(ksu_handle_execveat_sucompat);

// Stub for devpts hook
int ksu_handle_devpts(struct inode *inode)
{
    return 0;
}
EXPORT_SYMBOL(ksu_handle_devpts);

// Stub for input hook
int ksu_handle_input_handle_event(unsigned int *type, unsigned int *code, int *value)
{
    return 0;
}
EXPORT_SYMBOL(ksu_handle_input_handle_event);

// Stub for faccessat hook
int ksu_handle_faccessat(int *dfd, const char __user **filename_user, int *mode, int *flags)
{
    return 0;
}
EXPORT_SYMBOL(ksu_handle_faccessat);

// Stub for stat hook
int ksu_handle_stat(int *dfd, const char __user **filename_user, int *flags)
{
    return 0;
}
EXPORT_SYMBOL(ksu_handle_stat);
