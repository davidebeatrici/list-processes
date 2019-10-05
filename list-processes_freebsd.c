#include <stdlib.h>
#include <stdio.h>

#include <libutil.h>
#include <sys/types.h>
#include <sys/user.h>

int main()
{
	int n_procs;
	struct kinfo_proc *procs_info = kinfo_getallproc(&n_procs);
	if (!procs_info) {
		printf("kinfo_getallproc() failed\n");
		return 1;
	}

	for (int i = 0; i < n_procs; ++i) {
		printf("[%u] %s\n", procs_info[i].ki_pid, procs_info[i].ki_comm);
	}

	free(procs_info);

	return 0;
}
