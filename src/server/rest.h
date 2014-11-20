#ifndef _REST_H_
#define _REST_H_

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

bool is_REST_URI(const char* aURI);

void extract_group_name(const char* aURI, char *aGroupName, size_t groupLength, char *aName, size_t aNameLength);

#ifdef __cplusplus
}
#endif//__cplusplus

#endif//_REST_H_
