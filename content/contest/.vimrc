se nu ru cul cin ai is hls ls=2 bs=2 ts=3 sw=3 sts=3 et | sy on
" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
