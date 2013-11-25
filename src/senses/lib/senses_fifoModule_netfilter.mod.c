#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x15b2dc7b, "module_layout" },
	{ 0xf9a482f9, "msleep" },
	{ 0x13d0adf7, "__kfifo_out" },
	{ 0xd0d8621b, "strlen" },
	{ 0xc068440e, "__kfifo_alloc" },
	{ 0x85651533, "filp_close" },
	{ 0xc9ed65a2, "kthread_create_on_node" },
	{ 0x50eedeb8, "printk" },
	{ 0x4f79b22e, "kthread_stop" },
	{ 0xb4390f9a, "mcount" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x62c20484, "wake_up_process" },
	{ 0xdb760f52, "__kfifo_free" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xf23fcb99, "__kfifo_in" },
	{ 0xbd2136f8, "vfs_write" },
	{ 0xe914e41e, "strcpy" },
	{ 0xd3c60f8b, "filp_open" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "ACCF6EAF75B91029F36B883");
