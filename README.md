# DESCRIPTION
This repository contains the source files for the generation of the IEC61850-related application (publisher or subscriber) on two different platforms (WINDOWS or LINX). The purpose of the publisher is to generated the timestamp, integrate the timestamp into R-GOOSE message and send it over UDP to the client. The purpose of the subscriber is to receive a new R-GOOSE message sent by publisher, and calculate its latency (how long the message went from the publisher to the subscriber). Latency calculateion is based on difference between two timestamps (of the publisher and the subscribers) generated in moments of sending and receiving R-GOOSE message.

# IMPORTANT
Both the publisher and the subscriber should be synchronized before runing the latency test. Use third-party PTP server/client applications to do so. 
