////////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#ifndef __DEFINITIONS__
#define __DEFINITIONS__

#if defined(__PROTOCOL_77__)
#define __PROTOCOL_76__
#define ITEMS_PATH std::string("77")
#define OTB_VERSION 2
#define CLIENT_VERSION_MIN 1320
#define CLIENT_VERSION_MAX 1320
#define CLIENT_VERSION_STRING "Only Official Client allowed! Visit the website for more information."
#elif defined(__PROTOCOL_76__)
#define ITEMS_PATH std::string("76")
#define OTB_VERSION 1
#define CLIENT_VERSION_MIN 760
#define CLIENT_VERSION_MAX 760
#define CLIENT_VERSION_STRING "Only clients with protocol 7.60 allowed!"
#else
#define ITEMS_PATH std::string("74")
#define OTB_VERSION 1
#define CLIENT_VERSION_MIN 740
#define CLIENT_VERSION_MAX 740
#define CLIENT_VERSION_STRING "Only clients with protocol 7.40 allowed!"
#endif

#define SOFTWARE_NAME "Dura"
#define SOFTWARE_VERSION "Snapshot_2019_Version_2.0"
#define SOFTWARE_CODENAME "-"
#define SOFTWARE_DEVELOPERS "TFS Developers + Vizjus"
#if defined(__PROTOCOL_77__)
#define SOFTWARE_PROTOCOL "7.7x"
#elif defined(__PROTOCOL_76__)
#define SOFTWARE_PROTOCOL "7.60"
#else
#define SOFTWARE_PROTOCOL "7.40"
#endif

#define VERSION_PATCH 0
#define VERSION_DATABASE 38

#define MAX_RAND_RANGE 10000000
#ifndef __FUNCTION__
	#define	__FUNCTION__ __func__
#endif

#define BOOST_ASIO_ENABLE_CANCELIO 1
#ifdef _MSC_VER
	#define __PRETTY_FUNCTION__ __FUNCDNAME__
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

	#ifdef NDEBUG
		#define _SECURE_SCL 0
		#define HAS_ITERATOR_DEBUGGING 0
	#endif

	#include <cstring>
	#define atoll _atoi64
	#if VISUALC_VERSION < 10
		typedef unsigned long long uint64_t;
		typedef signed long long int64_t;
		typedef unsigned int uint32_t;
		typedef signed int int32_t;
		typedef unsigned short uint16_t;
		typedef signed short int16_t;
		typedef unsigned char uint8_t;
		typedef signed char int8_t;
	#endif

	#pragma warning(disable:4786) // msvc too long debug names in stl
	#pragma warning(disable:4250) // 'class1' : inherits 'class2::member' via dominance
	#pragma warning(disable:4244)
	#pragma warning(disable:4267)
	#pragma warning(disable:4018)
	#pragma warning(disable:4309)
	#pragma warning(disable:4996) // '_ftime64' : this function or variable may be unsafe

	#ifndef _WIN32
		#define _WIN32
	#endif
	#ifndef WIN32
		#define WIN32
	#endif

	#ifndef __WINDOWS__
		#define __WINDOWS__
	#endif
	#ifndef WINDOWS
		#define WINDOWS
	#endif
#else
	#if defined _WIN32 || defined WIN32 || defined __WINDOWS__ || defined WINDOWS
		#ifndef _WIN32
			#define _WIN32
		#endif
		#ifndef WIN32
			#define WIN32
		#endif

		#ifndef __WINDOWS__
			#define __WINDOWS__
		#endif
		#ifndef WINDOWS
			#define WINDOWS
		#endif
	#endif

	#ifdef __CYGWIN__
		#undef WIN32
		#undef _WIN32
		#undef WINDOWS
		#undef __WINDOWS__
		#define HAVE_ERRNO_AS_DEFINE
	#endif
#endif

#ifdef __WINDOWS__
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif

	//Windows 2000	0x0500
	//Windows XP	0x0501
	//Windows 2003	0x0502
	//Windows Vista	0x0600
	//Windows Seven 0x0601

	#define _WIN32_WINNT 0x0501
#elif defined __GNUC__
	#define __USE_ZLIB__
#endif

#ifdef __MINGW32__
	#define XML_GCC_FREE
#endif

#ifdef XML_GCC_FREE
	#define xmlFree(s) free(s)
#endif

#ifndef __EXCEPTION_TRACER__
	#define DEBUG_REPORT
#endif
#endif
