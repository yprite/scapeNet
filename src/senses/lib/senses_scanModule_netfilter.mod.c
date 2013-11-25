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
	{ 0x4afe531b, "nf_unregister_hooks" },
	{ 0x138828c9, "nf_register_hooks" },
	{ 0xd7a5e6b0, "skb_copy" },
	{ 0x50eedeb8, "printk" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x61651be, "strcat" },
	{ 0x11fe12ba, "set_kfifo" },
	{ 0x91715312, "sprintf" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=senses_fifoModule_netfilter";


MODULE_INFO(srcversion, "4C09F0330EEA3D5AF0D24A9");
