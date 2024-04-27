#include <alinix/kernel.h>
#include <alinix/kobject.h>
#include <alinix/kern_levels.h>

void kobject_put(struct kobject *kobj)
{
	if (kobj) {
		if (!kobj->state_initialized)
			WARN(1, KERN_WARNING
				"kobject: '%s' (%p): is not initialized, yet kobject_put() is being called.\n",
			     kobject_name(kobj), kobj);
		kref_put(&kobj->kref, kobject_release);
	}
}


void kobject_del(struct kobject *kobj)
{
	struct kobject *parent;

	if (!kobj)
		return;

	parent = kobj->parent;
	__kobject_del(kobj);
	kobject_put(parent);
}

