{$
#include <iostream>
#include <vector>
$}

handlername = galois;
namespace=galois::freyja;

create datasource gbus {
    property {
        type = databus;
        protourl = ssh://git@github.com/galois-advertising/common/master/databus.proto:90000;
    };
};