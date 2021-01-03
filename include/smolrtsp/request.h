/**
 * @file
 *  An RTSP request.
 */

#ifndef SMOLRTSP_REQUEST_H
#define SMOLRTSP_REQUEST_H

#include <smolrtsp/header_map.h>
#include <smolrtsp/message_body.h>
#include <smolrtsp/request_line.h>

#include <stdbool.h>

/**
 * An RTSP request.
 */
typedef struct {
    SmolRTSP_RequestLine start_line;
    SmolRTSP_HeaderMap header_map;
    SmolRTSP_MessageBody body;
} SmolRTSP_Request;

/**
 * Tests @p lhs and @p rhs for equality.
 *
 * @return `true` if @p lhs and @rhs are equal, `false` otherwise.
 *
 * `lhs != NULL`
 * `rhs != NULL`
 */
bool SmolRTSP_Request_eq(
    const SmolRTSP_Request *restrict lhs, const SmolRTSP_Request *restrict rhs);

#endif // SMOLRTSP_REQUEST_H
