/**
 * @file
 * @brief An RTSP response.
 */

#pragma once

#include <smolrtsp/types/error.h>
#include <smolrtsp/types/header_map.h>
#include <smolrtsp/types/message_body.h>
#include <smolrtsp/types/response_line.h>

#include <stdbool.h>

#include <smolrtsp/priv/compiler_attrs.h>

/**
 * An RTSP response.
 */
typedef struct {
    /**
     * The response line.
     */
    SmolRTSP_ResponseLine start_line;

    /**
     * The header map.
     */
    SmolRTSP_HeaderMap header_map;

    /**
     * The message body.
     */
    SmolRTSP_MessageBody body;

    /**
     * The sequence number for an RTSP request/response pair.
     */
    uint32_t cseq;
} SmolRTSP_Response;

/**
 * Serialises @p self into @p w.
 *
 * #SmolRTSP_Response.cseq is serialised automatically as a first header -- you
 * need not to present it in #SmolRTSP_Response.header_map.
 *
 * @param[in] self The instance to be serialised.
 * @param[in] w The writer to be provided with serialised data.
 *
 * @return The number of bytes written or a negative value on error.
 *
 * @pre `w.self && w.vptr`
 */
ssize_t SmolRTSP_Response_serialize(SmolRTSP_Response self, SmolRTSP_Writer w)
    SMOLRTSP_PRIV_MUST_USE;

/**
 * Parses @p data to @p self.
 *
 * @pre `self != NULL`
 */
SmolRTSP_ParseResult SmolRTSP_Response_parse(
    SmolRTSP_Response *restrict self, CharSlice99 input) SMOLRTSP_PRIV_MUST_USE;

/**
 * Tests @p lhs and @p rhs for equality.
 */
bool SmolRTSP_Response_eq(SmolRTSP_Response lhs, SmolRTSP_Response rhs)
    SMOLRTSP_PRIV_MUST_USE;

/**
 * The same as #smolrtsp_respond_with_body but with an empty message body.
 */
ssize_t smolrtsp_respond(
    SmolRTSP_Writer w, uint32_t cseq, SmolRTSP_StatusCode code,
    const char *reason, SmolRTSP_HeaderMap headers);

/**
 * Writes an RTSP response to @p w.
 *
 * @param[out] w The writer to be provided with the response.
 * @param[in] cseq The sequence number for an RTSP request/response pair.
 * @param[in] code The RTSP status code.
 * @param[in] reason The RTSP reason phrase.
 * @param[in] headers The response headers. Do not include `CSeq` in it; `CSeq`
 * will be serialised automatically as a first header.
 * @param[in] body The RTSP message body.
 *
 * @return The number of bytes written or a negative value on error.
 */
ssize_t smolrtsp_respond_with_body(
    SmolRTSP_Writer w, uint32_t cseq, SmolRTSP_StatusCode code,
    const char *reason, SmolRTSP_HeaderMap headers, SmolRTSP_MessageBody body);