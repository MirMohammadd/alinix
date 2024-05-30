/**
 * @file kobject.c
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 * 	- implements kernel objects.
*/
#include <alinix/kernel.h>
#include <alinix/kobject.h>
#include <alinix/kern_levels.h>

// void kobject_put(struct kobject *kobj)
// {
// 	if (kobj) {
// 		if (!kobj->state_initialized)
// 			WARN(1, KERN_WARNING
// 				"kobject: '%s' (%p): is not initialized, yet kobject_put() is being called.\n",
// 			     kobject_name(kobj), kobj);
// 		kref_put(&kobj->kref, kobject_release);
// 	}
// }

// static void __kobject_del(struct kobject *kobj)
// {
// 	struct kernfs_node *sd;
// 	const struct kobj_type *ktype;

// 	sd = kobj->sd;
// 	ktype = get_ktype(kobj);

// 	if (ktype)
// 		sysfs_remove_groups(kobj, ktype->default_groups);

// 	/* send "remove" if the caller did not do it but sent "add" */
// 	if (kobj->state_add_uevent_sent && !kobj->state_remove_uevent_sent) {
// 		pr_debug("'%s' (%p): auto cleanup 'remove' event\n",
// 			 kobject_name(kobj), kobj);
// 		kobject_uevent(kobj, KOBJ_REMOVE);
// 	}

// 	sysfs_remove_dir(kobj);
// 	sysfs_put(sd);

// 	kobj->state_in_sysfs = 0;
// 	kobj_kset_leave(kobj);
// 	kobj->parent = NULL;
// }



// static void kobj_kset_leave(struct kobject *kobj)
// {
// 	if (!kobj->kset)
// 		return;

// 	spin_lock(&kobj->kset->list_lock);
// 	list_del_init(&kobj->entry);
// 	spin_unlock(&kobj->kset->list_lock);
// 	kset_put(kobj->kset);
// }

// void kobject_init(struct kobject *kobj, const struct kobj_type *ktype)
// {
// 	char *err_str;

// 	if (!kobj) {
// 		err_str = "invalid kobject pointer!";
// 		goto error;
// 	}
// 	if (!ktype) {
// 		err_str = "must have a ktype to be initialized properly!\n";
// 		goto error;
// 	}
// 	if (kobj->state_initialized) {
// 		/* do not error out as sometimes we can recover */
// 		pr_err("kobject (%p): tried to init an initialized object, something is seriously wrong.\n",
// 		       kobj);
// 		dump_stack_lvl(KERN_ERR);
// 	}

// 	kobject_init_internal(kobj);
// 	kobj->ktype = ktype;
// 	return;

// error:
// 	pr_err("kobject (%p): %s\n", kobj, err_str);
// 	dump_stack_lvl(KERN_ERR);
// }