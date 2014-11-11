#include "slre.h"
#include <string.h>
#include <stdbool.h>

static const char * regex = "^/group/([^/]+)/name/([^/]+)$";

bool is_REST_URI(const char* aURI)
{
	int result = slre_match(regex, aURI, strlen(aURI), NULL, 0, 0);
	return (result >= 0);
}

void extract_group_name(const char* aURI, char *aGroupName, size_t groupLength, char *aName, size_t aNameLength)
{
	struct slre_cap match[2];
	//FIXME should we limit the size?
	int result = slre_match(regex, aURI, strlen(aURI), match, 2, 0);
	memcpy(aGroupName, match[0].ptr, match[0].len); //FIXME actually limit the size
	memcpy(aName, match[1].ptr, match[1].len); //FIXME actually limit the size
}
