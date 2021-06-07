set -e

if [ "$#" -ne 1 ]
then
    echo "Usage: $0 PCAP"
    exit 1
fi

NL="
"

(
set -x
tcpdump -nXXr "$1"
tcpdump -nAr "$1"
tcpdump -nr "$1"
tshark -nxr "$1"
tshark -nr "$1"
) 2>&1 | sed "s/^+/\\$NL\$/" | tail -n +2
