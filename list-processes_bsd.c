#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include <fcntl.h>
#include <kvm.h>
#include <paths.h>
#include <sys/sysctl.h>
#include <sys/user.h>

bool kvm_cleanup(kvm_t *kd)
{
	if (kvm_close(kd) == -1) {
		printf("kvm_close() failed with error %d\n", errno);
		return false;
	}

	return true;
}

int main()
{
	char error[_POSIX2_LINE_MAX];
#ifdef KVM_NO_FILES
	kvm_t *kd = kvm_openfiles(NULL, NULL, NULL, KVM_NO_FILES, error);
#else
	kvm_t *kd = kvm_openfiles(NULL, _PATH_DEVNULL, NULL, O_RDONLY, error);
#endif
	if (!kd) {
		printf("kvm_open2() failed with error: %s\n", error);
		return 1;
	}

	int n_procs;
	struct kinfo_proc *procs_info = kvm_getprocs(kd, KERN_PROC_PROC, 0, &n_procs);
	if (!procs_info) {
		printf("kvm_getprocs() failed\n");
		kvm_cleanup(kd);
		return 2;
	}

	for (int i = 0; i < n_procs; ++i) {
		printf("[%u] %s\n", procs_info[i].ki_pid, procs_info[i].ki_comm);
	}

	if (!kvm_cleanup(kd)) {
		return 3;
	}

	return 0;
}
