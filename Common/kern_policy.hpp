//
//  kern_policy.hpp
//  KernelCommon
//
//  Copyright © 2016 vit9696. All rights reserved.
//

#ifndef kern_policy_hpp
#define kern_policy_hpp

#include <sys/types.h>
#include <sys/proc.h>

extern "C" {
	#include <security/mac_framework.h>
	#include <security/mac_policy.h>
}

#include "kern_util.hpp"

class Policy {
	/**
	 *  TrustedBSD Policy handle
	 */
	mac_policy_handle_t policyHandle {0};
	
	/**
	 *  TrustedBSD policy configuration
	 */
	mac_policy_conf policyConf;
public:
	/**
	 *  May be used at TrustedBSD policy initialisation
	 *
	 *  @param conf policy configuration
	 */
	static void dummyPolicyInitBSD(mac_policy_conf *conf) {
		DBGLOG("policy @ init bsd");
	}
	
	/**
	 *  Compile-time policy constructor
	 *
	 *  @param name  policy name literal
	 *  @param descr policy description literal
	 *  @param ops   policy functions
	 */
	constexpr Policy(const char *name, const char *descr, struct mac_policy_ops *ops) : policyConf{
		.mpc_name				= name,
		.mpc_fullname			= descr,
		.mpc_labelnames			= nullptr,
		.mpc_labelname_count	= 0,
		.mpc_ops				= ops,
		// Our policies are loaded very early and are static. We cannot unload them.
		.mpc_loadtime_flags		= 0 /*MPC_LOADTIME_FLAG_UNLOADOK*/,
		.mpc_field_off			= nullptr,
		.mpc_runtime_flags		= 0
	} { }
	
	/**
	 *  Registers TrustedBSD policy
	 *
	 *  @return true on success
	 */
	bool registerPolicy();
	
	/**
	 *  Unregisters TrustedBSD policy if allowed
	 *
	 *  @return true on success
	 */
	bool unregisterPolicy();
};

#endif /* kern_policy_hpp */
