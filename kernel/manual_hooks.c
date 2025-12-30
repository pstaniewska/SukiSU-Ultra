// Manual hooks compatibility layer for SukiSU Ultra
// Bridges kernel manual hook calls to SukiSU internal functions
#include <linux/export.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fdtable.h>
#include <linux/err.h>

// Hook enable flags - defined in ksud.c, just declare extern here
extern bool ksu_execveat_hook;
extern bool ksu_vfs_read_hook;

// Forward declarations of internal SukiSU functions from ksud.c
extern int ksu_handle_execveat_ksud(int *fd, struct filename **filename_ptr,
                                    void *argv, void *envp, int *flags);
extern int ksu_handle_vfs_read(struct file **file_ptr, char __user **buf_ptr,
                               size_t *count_ptr, loff_t **pos);

// Forward declaration from sucompat.c
extern int ksu_handle_execve_sucompat(const char __user **filename_user,
                                      void *argv, void *envp, int *flags);

// Wrapper for sys_read hook - kernel calls this from read_write.c
// Converts fd to file* and delegates to ksud's vfs_read handler
int ksu_handle_sys_read(unsigned int fd, char __user **buf_ptr, size_t *count_ptr)
{
    struct fd f;
    struct file *file;
    int ret;

    if (!ksu_vfs_read_hook)
        return 0;

    f = fdget(fd);
    if (!f.file)
        return 0;

    file = f.file;
    ret = ksu_handle_vfs_read(&file, buf_ptr, count_ptr, NULL);
    fdput(f);
    return ret;
}
EXPORT_SYMBOL(ksu_handle_sys_read);

// Wrapper for execveat hook - kernel calls this from exec.c
// Delegates to ksud's execveat handler
int ksu_handle_execveat(int *fd, struct filename **filename_ptr,
                        void *argv, void *envp, int *flags)
{
    if (!ksu_execveat_hook)
        return 0;

    return ksu_handle_execveat_ksud(fd, filename_ptr, argv, envp, flags);
}
EXPORT_SYMBOL(ksu_handle_execveat);

// Wrapper for execveat sucompat hook - kernel calls this from exec.c
// Converts struct filename to user string and delegates to sucompat
int ksu_handle_execveat_sucompat(int *fd, struct filename **filename_ptr,
                                 void *argv, void *envp, int *flags)
{
    struct filename *filename;
    const char __user *uptr;

    if (!ksu_execveat_hook)
        return 0;

    if (!filename_ptr)
        return 0;

    filename = *filename_ptr;
    if (IS_ERR_OR_NULL(filename))
        return 0;

    uptr = filename->uptr;
    if (!uptr)
        return 0;

    return ksu_handle_execve_sucompat(&uptr, argv, envp, flags);
}
EXPORT_SYMBOL(ksu_handle_execveat_sucompat);
