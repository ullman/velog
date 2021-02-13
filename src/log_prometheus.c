/*
Copyright (C) 2021  Henrik Ullman
License: GPL Version 3
*/

#include <prom.h>
#include <promhttp.h>
#include <microhttpd.h>

#include "log_prometheus.h"


prom_gauge_t *velog_gauge;


void	init_prometheus(void){
  prom_collector_registry_default_init();
}

void init_metric_prometheus(void){
  velog_gauge = prom_collector_registry_must_register_metric (prom_gauge_new ("velog_gauge", "exports victron data", 1, (const char *[]) {"label"}));
}

int log_prometheus(const char* label, double value){
  return prom_gauge_set (velog_gauge, value, (const char *[]) { label });
}

void close_prometheus(void){
  prom_collector_registry_destroy (PROM_COLLECTOR_REGISTRY_DEFAULT);
}

