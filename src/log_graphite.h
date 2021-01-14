/*
Copyright (C) 2020  Philip Freeman <elektron@halo.nu>
License: GPL Version 3
*/

#ifndef LOG_GRAPHITE_CLIENT_H
#define LOG_GRAPHITE_CLIENT_H

int	init_graphite(char *host, int port);
void	close_graphite(void);
void	log_graphite(char* path_in, float value, unsigned long ts);

#endif /* LOG_GRAPHITE_CLIENT_H */
