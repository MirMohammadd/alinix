#ifndef _CPUID_H
#define _CPUID_H

#include <stddef.h>

#define ECX_FLAGS_SIZE 24
#define EDX_FLAGS_SIZE 32

struct cpuinfo_generic {
    char *cpu_vendor;
    char *cpu_type;
    int cpu_family;
    int cpu_model;
    int apic_id;
    int cpuid_ecx_flags[ECX_FLAGS_SIZE];
    int cpuid_edx_flags[EDX_FLAGS_SIZE];
    int is_brand_string;
    char *brand_string;
};

struct registri {
    int eax;
    int ebx;
    int ecx;
    int edx;
};

char cpu_vendor[12]; // This will contain the main string
void get_cpuid (struct cpuinfo_generic *);

void call_cpuid (struct registri *);
void cpuid_write_vendor (struct cpuinfo_generic *, struct registri *);
void cpuid_write_proctype (struct cpuinfo_generic *, struct registri *);
void cpuid_feature_ecx (struct cpuinfo_generic *, int);
void cpuid_feature_edx (struct cpuinfo_generic *, int);
int cpuid_get_byte (int, int, int);

char *cpuid_brand_index (struct registri *);
char *cpuid_brand_string (struct registri *);

struct cpuinfo_generic *sinfo;
#endif
