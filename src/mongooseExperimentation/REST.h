#ifndef _REST_H_
#define _REST_H_

bool is_REST_URI(const char* aURI);

void extract_group_name(const char* aURI, char *aGroupName, size_t groupLength, char *aName, size_t aNameLength);


#endif//_REST_H_
