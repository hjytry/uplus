
#ifndef __UPLUS_PAL_DEF_H__
#define __UPLUS_PAL_DEF_H__

#ifdef USE_C_LIB

/* os */
#define TIME_NO_WAIT                0
#define TIME_WAIT_FOREVER           0
#define SEM_TAKE_TIMEOUT            0
#define uplus_os_task_delete
#define uplus_os_task_sleep
#define uplus_os_mutex_create
#define uplus_os_mutex_take
#define uplus_os_mutex_give
#define uplus_os_mutex_delete
#define uplus_os_sem_create
#define uplus_os_sem_take
#define uplus_os_sem_give
#define uplus_os_sem_delete
#define uplus_os_current_time_get   uplus_sys_uptime_get
#define uplus_os_diff_time_cal

#define uplus_tool_malloc           malloc
#define uplus_tool_free             free
#define uplus_tool_safe_malloc      safe_malloc
#define uplus_tool_safe_free        safe_free

#define uplus_tool_memcpy           memcpy
#define uplus_tool_memmove         
#define uplus_tool_memset           memset
#define uplus_tool_memcmp           memcmp
#define uplus_tool_memchr 
#define uplus_tool_strncmp          strncmp
#define uplus_tool_strcmp           strcmp
#define uplus_tool_strncpy          strncpy
#define uplus_tool_strcpy           strcpy
#define uplus_tool_strlen           strlen
#define uplus_tool_strcasecmp       strcasecmp
#define uplus_tool_strncasecmp 
#define uplus_tool_atoi             
#define uplus_tool_isdigit          
#define uplus_tool_isalnum           
#define uplus_tool_isprint         
     
#define uplus_tool_sprintf          sprintf
#define uplus_tool_snprintf         snprintf
#define uplus_tool_vsnprintf        
#define uplus_tool_rand             uplus_rand
#define uplus_tool_srand            uplus_srand

#define uplus_net_htons
#define uplus_net_ntohs
#define uplus_net_htonl
#define uplus_net_ntohl

#endif

#endif /*__UPLUS_PAL_DEF_H__*/

