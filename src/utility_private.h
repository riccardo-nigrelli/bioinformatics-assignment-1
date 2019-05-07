#ifndef UTILITY_PRIVATE_H

	#define UTILITY_PRIVATE_H

	#include <tool/utility.h>

	struct eulerian_path_s {
		int id;
		struct eulerian_path_s *next;
	};

#endif /* UTILITY_PRIVATE_H */
