#! /bin/bash

#使用yum 安装的boost 只有so 没有.a 
#自己编译boost， cp 到 /usr/lib64下



thrift_bin=../bin/thrift
thrift_bin=../bin/thrift_0.10

${thrift_bin} -r --gen cpp rda.thrift
${thrift_bin} -r --gen java rda.thrift
${thrift_bin} -r --gen py rda.thrift


