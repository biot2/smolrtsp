#include <smolrtsp/types/header_map.h>

#include "crlf.h"
#include "parsing.h"

#include <assert.h>
#include <string.h>

SmolRTSP_HeaderMap SmolRTSP_HeaderMap_empty(void) {
    return (SmolRTSP_HeaderMap){.headers = NULL, .len = 0, .capacity = 0};
}

bool SmolRTSP_HeaderMap_find(
    SmolRTSP_HeaderMap self, CharSlice99 key, CharSlice99 *restrict value) {
    assert(value);

    for (size_t i = 0; i < self.len; i++) {
        if (CharSlice99_primitive_eq(self.headers[i].key, key)) {
            *value = self.headers[i].value;
            return true;
        }
    }

    return false;
}

bool SmolRTSP_HeaderMap_key_is_present(SmolRTSP_HeaderMap self, CharSlice99 key) {
    CharSlice99 value;
    return SmolRTSP_HeaderMap_find(self, key, &value);
}

void SmolRTSP_HeaderMap_serialize(SmolRTSP_HeaderMap self, SmolRTSP_Writer w) {
    assert(w.self && w.vptr);

    for (size_t i = 0; i < self.len; i++) {
        SmolRTSP_Header_serialize(self.headers[i], w);
    }

    VCALL(w, write, SMOLRTSP_CRLF);
}

SmolRTSP_ParseResult
SmolRTSP_HeaderMap_parse(SmolRTSP_HeaderMap *restrict self, CharSlice99 input) {
    assert(self);

    const CharSlice99 backup = input;

    while (true) {
        if (input.len < SMOLRTSP_CRLF.len) {
            return SmolRTSP_ParseResult_partial(0);
        }

        if (CharSlice99_primitive_starts_with(input, SMOLRTSP_CRLF)) {
            return SmolRTSP_ParseResult_complete((input.ptr - backup.ptr) + SMOLRTSP_CRLF.len);
        }

        if (SmolRTSP_HeaderMap_is_full(*self)) {
            return SmolRTSP_ParseResult_Failure(SmolRTSP_ParseError_HeaderMapOverflow());
        }

        SmolRTSP_Header header;
        MATCH(SmolRTSP_Header_parse(&header, input));
        self->headers[self->len] = header;
        self->len++;
    }
}

bool SmolRTSP_HeaderMap_eq(SmolRTSP_HeaderMap lhs, SmolRTSP_HeaderMap rhs) {
    if (lhs.len != rhs.len) {
        return false;
    }

    const size_t len = lhs.len;

    for (size_t i = 0; i < len; i++) {
        if (!SmolRTSP_Header_eq(lhs.headers[i], rhs.headers[i])) {
            return false;
        }
    }

    return true;
}

bool SmolRTSP_HeaderMap_is_full(SmolRTSP_HeaderMap self) {
    return self.len == self.capacity;
}

void SmolRTSP_HeaderMap_dbg_to_file(SmolRTSP_HeaderMap self, FILE *stream) {
    assert(stream);

    for (size_t i = 0; i < self.len; i++) {
        SmolRTSP_Header_dbg_to_file(self.headers[i], stream);
    }
}

void SmolRTSP_HeaderMap_dbg(SmolRTSP_HeaderMap self) {
    SmolRTSP_HeaderMap_dbg_to_file(self, stderr);
}