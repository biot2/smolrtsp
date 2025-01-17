# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## unreleased

## 0.1.2 - 2022-07-27

### Fixed

 - Suppress a compilation warning for an unused variable in `smolrtsp_vheader`.
 - Overflow while computing an RTP timestamp.

## 0.1.1 - 2022-03-31

### Fixed

 - Mark the following functions with `__attribute__((warn_unused_result))` (when available):
   - `SmolRTSP_ParseError_print`.
   - `SmolRTSP_MessageBody_empty`.
   - `SmolRTSP_Request_uninit`.
   - `SmolRTSP_Response_uninit`.
   - `SmolRTSP_NalTransportConfig_default`.
   - `smolrtsp_determine_start_code`.
   - `smolrtsp_dgram_socket`.

## 0.1.0 - 2022-03-30

### Added

 - This awesome library.
