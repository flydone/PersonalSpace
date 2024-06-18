#! /vendor/bin/sh

set -o errexit

usage() {
cat <<USAGE

Usage:
    $0 [OPTIONS] <PARAMETER>

Description:
    Start ETS client or service, service can run with parameter.

OPTIONS:
    -c      start ETS client application
    -s      start ETS service application with or without parameters

PARAMETER:
    just used for starting ETS service
    ms      start ETS service support multiple services
    mi      start ETS service support multiple instances in one service.

USAGE
}

if [ $# -gt 2 ]; then
    echo "\n please don't input more than 2 parameters!"
    usage;
    exit 0;
elif [ "$1" = "-h" ]; then
    usage;
    exit 0;
elif [ "$1" = "-c" ]; then
    echo "\n start ETS client application"
    export VSOMEIP_CONFIGURATION=/vendor/etc/someip/ETS_Client_UDP.json
    export VSOMEIP_APPLICATION_NAME=SomeIP-ETS-Client
    /vendor/bin/etsclient
elif [ "$1" = "-s" ]; then
    export VSOMEIP_CONFIGURATION=/vendor/etc/someip/ETS_Service_UDP.json
    export VSOMEIP_APPLICATION_NAME=SomeIP-ETS-Service
    if [ "$2" = "ms" ]; then
        echo "\n start ETS client application with multiple services"
        /vendor/bin/etsserver SERVICES
    elif [ "$2" = "mi" ]; then
        echo "\n start ETS client application with multiple instances"
        /vendor/bin/etsserver INSTANCES
    else
        echo "\n start ETS client application"
        /vendor/bin/etsserver
    fi
else
    usage;
    exit 0;
fi
