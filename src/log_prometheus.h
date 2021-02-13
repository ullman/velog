/*
Copyright (C) 2021  Henrik Ullman
License: GPL Version 3
*/

#ifndef LOG_PROMETHEUS_CLIENT_H
#define LOG_PROMETHEUS_CLIENT_H


void init_prometheus(void);

void init_metric_prometheus(void);

int log_prometheus(const char* label, double value);

void close_prometheus(void);

#endif /* LOG_PROMETHEUS_CLIENT_H */
