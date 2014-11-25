#ifndef _OUROBOROS_REST_H_
#define _OUROBOROS_REST_H_


namespace ouroboros
{
	bool is_REST_URI(const char* aURI);

	void extract_group(
		const char* aURI,
		char *aGroupName,
		size_t groupLength);

	void extract_group_name(
		const char* aURI,
		char *aGroupName,
		size_t groupLength,
		char *aName,
		size_t aNameLength);
}

#endif//_OUROBOROS_REST_H_
