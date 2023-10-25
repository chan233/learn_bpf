
#include <linux/bpf.h>

#define SEC(NAME) __attribute__((section(NAME), used)) 
//SEC 属性告知 BPF 虚拟机何时运行此程序

SEC("tracepoint/syscalls/sys_enter_execve") 
// 当检测到 execve 系统调用跟踪点被执行时，BPF 程序将运行 。
// 跟踪点是内核二进制代码中的静态标记，允许开发人员注入代码来检查内核的执行

//execve 是执行其他程序的指令。当内核检测到 execve 执行时，


int bpf_prog(void *ctx) {
    char msg[] = "Hello, BPF world!\n";
    bpf_trace_printk(msg, sizeof(msg));
    return 0;
}
// BPF 程序被执行，我们会看到消息输出 Hello ， BPF World ! 
char _license[] SEC("license") = "GPL";

// 我们还需要指定程序许可证。因为 Linux 内核采用 GPL 许可证，所以它只能加载 GPL 许可证的程序。
// 如果将程序设置为其他许可证，内核将拒绝加载该程序。

//编译程序
//clang -O2 -target bpf -c helloworld.c -o bpf_helloworld.o
//加载到内核