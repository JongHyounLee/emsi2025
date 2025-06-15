#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x31a4702a, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x772d282a, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xac39b407, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xb590822d, __VMLINUX_SYMBOL_STR(hrtimer_start) },
	{ 0x54d8b7ba, __VMLINUX_SYMBOL_STR(hrtimer_init) },
	{ 0x56b15ac3, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0xadf661fa, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xe4c4b28f, __VMLINUX_SYMBOL_STR(gpiod_direction_output) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0x1b3085da, __VMLINUX_SYMBOL_STR(pinctrl_select_state) },
	{ 0xfcdf0f15, __VMLINUX_SYMBOL_STR(pinctrl_lookup_state) },
	{ 0xd537d632, __VMLINUX_SYMBOL_STR(devm_pinctrl_get) },
	{ 0xa12d929d, __VMLINUX_SYMBOL_STR(desc_to_gpio) },
	{ 0x368382e2, __VMLINUX_SYMBOL_STR(of_get_named_gpiod_flags) },
	{ 0xc6b8969f, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x931edd3f, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xd556e49d, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x9a47820d, __VMLINUX_SYMBOL_STR(hrtimer_forward) },
	{ 0xc87c1f84, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0x8a1e4265, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x2745bec5, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x1e2f85a3, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x4b0ac955, __VMLINUX_SYMBOL_STR(hrtimer_cancel) },
	{ 0x687934e9, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0xf816c866, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x89ee190, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Ccndi,perifnd*");
MODULE_ALIAS("platform:perifnd");
