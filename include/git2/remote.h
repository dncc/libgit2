/*
 * Copyright (C) 2009-2011 the libgit2 contributors
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_git_remote_h__
#define INCLUDE_git_remote_h__

#include "common.h"
#include "repository.h"
#include "refspec.h"
/**
 * @file git2/remote.h
 * @brief Git remote management functions
 * @defgroup git_remote remote management functions
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/*
 * TODO: This functions still need to be implemented:
 * - _listcb/_foreach
 * - _add
 * - _rename
 * - _del (needs support from config)
 */

/**
 * Create a remote in memory
 *
 * Create a remote with the default refspecs in memory. You can use
 * this when you have a URL instead of a remote's name.
 *
 * @param out pointer to the new remote object
 * @param repo the associtated repository
 * @param url the remote repository's URL
 * @param name the remote's name
 * @return GIT_SUCCESS or an error code
 */
int git_remote_new(git_remote **out, git_repository *repo, const char *url, const char *name);

/**
 * Get the information for a particular remote
 *
 * @param out pointer to the new remote object
 * @param cfg the repository's configuration
 * @param name the remote's name
 * @return GIT_SUCCESS or an error code
 */
GIT_EXTERN(int) git_remote_get(struct git_remote **out, struct git_config *cfg, const char *name);

/**
 * Get the remote's name
 *
 * @param remote the remote
 * @return a pointer to the name
 */
GIT_EXTERN(const char *) git_remote_name(struct git_remote *remote);

/**
 * Get the remote's url
 *
 * @param remote the remote
 * @return a pointer to the url
 */
GIT_EXTERN(const char *) git_remote_url(struct git_remote *remote);

/**
 * Get the fetch refspec
 *
 * @param remote the remote
 * @return a pointer to the fetch refspec or NULL if it doesn't exist
 */
GIT_EXTERN(const git_refspec *) git_remote_fetchspec(struct git_remote *remote);

/**
 * Get the push refspec
 *
 * @param remote the remote
 * @return a pointer to the push refspec or NULL if it doesn't exist
 */

GIT_EXTERN(const git_refspec *) git_remote_pushspec(struct git_remote *remote);

/**
 * Open a connection to a remote
 *
 * The transport is selected based on the URL. The direction argument
 * is due to a limitation of the git protocol (over TCP or SSH) which
 * starts up a specific binary which can only do the one or the other.
 *
 * @param remote the remote to connect to
 * @param direction whether you want to receive or send data
 * @return GIT_SUCCESS or an error code
 */
GIT_EXTERN(int) git_remote_connect(struct git_remote *remote, int direction);

/**
 * Get a list of refs at the remote
 *
 * The remote (or more exactly its transport) must be connected. The
 * memory belongs to the remote.
 *
 * @param refs where to store the refs
 * @param remote the remote
 * @return GIT_SUCCESS or an error code
 */
GIT_EXTERN(int) git_remote_ls(git_remote *remote, git_headarray *refs);

/**
 * Download the packfile
 *
 * Negotiate what objects should be downloaded and download the
 * packfile with those objects. The packfile is downloaded with a
 * temporary filename, as it's final name is not known yet. If there
 * was no packfile needed (all the objects were available locally),
 * filename will be NULL and the function will return success.
 *
 * @param remote the remote to download from
 * @param filename where to store the temproray filename
 * @return GIT_SUCCESS or an error code
 */
GIT_EXTERN(int) git_remote_download(char **filename, git_remote *remote);

/**
 * Check whether the remote is connected
 *
 * Check whether the remote's underlying transport is connected to the
 * remote host.
 *
 * @return 1 if it's connected, 0 otherwise.
 */
GIT_EXTERN(int) git_remote_connected(git_remote *remote);

/**
 * Disconnect from the remote
 *
 * Close the connection to the remote and free the underlying
 * transport.
 *
 * @param remote the remote to disconnect from
 */
GIT_EXTERN(void) git_remote_disconnect(git_remote *remote);

/**
 * Free the memory associated with a remote
 *
 * @param remote the remote to free
 */
GIT_EXTERN(void) git_remote_free(struct git_remote *remote);

/**
 * Update the tips to the new state
 *
 * Make sure that you only call this once you've successfully indexed
 * or expanded the packfile.
 *
 * @param remote the remote to update
 */
GIT_EXTERN(int) git_remote_update_tips(struct git_remote *remote);

/** @} */
GIT_END_DECL
#endif
