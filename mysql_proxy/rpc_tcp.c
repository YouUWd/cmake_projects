//#if (HAVE_CONFIG_H)
//#include "../include/config.h"
//#endif
//
//#include "./libnet_test.h"
//
//int
//main(int argc, char **argv) {
//    int c;
//    char *cp;
//    libnet_t *l;
//    libnet_ptag_t t;
//    char *payload;
//    u_short payload_s;
//    u_long src_ip, dst_ip;
//    u_short src_prt, dst_prt;
//    char errbuf[LIBNET_ERRBUF_SIZE];
//
//    printf("libnet 1.1 packet shaping: RPC TCP[raw]\n");
//
//    /*
//     *  Initialize the library.  Root priviledges are required.
//     */
//    l = libnet_init(
//            LIBNET_RAW4,                            /* injection type */
//            NULL,                                   /* network interface */
//            errbuf);                                /* errbuf */
//
//    if (l == NULL) {
//        fprintf(stderr, "libnet_init() failed: %s", errbuf);
//        exit(EXIT_FAILURE);
//    }
//
//    src_ip = 0;
//    dst_ip = 0;
//    src_prt = 0;
//    dst_prt = 0;
//    payload = NULL;
//    payload_s = 0;
//    while ((c = getopt(argc, argv, "d:s:p:")) != EOF) {
//        switch (c) {
//            /*
//             *  We expect the input to be of the form `ip.ip.ip.ip.port`.  We
//             *  point cp to the last dot of the IP address/port string and
//             *  then seperate them with a NULL byte.  The optarg now points to
//             *  just the IP address, and cp points to the port.
//             */
//            case 'd':
//                if (!(cp = strrchr(optarg, '.'))) {
//                    usage(argv[0]);
//                }
//                *cp++ = 0;
//                dst_prt = (u_short) atoi(cp);
//                if ((dst_ip = libnet_name2addr4(l, optarg, LIBNET_RESOLVE)) == -1) {
//                    fprintf(stderr, "Bad destination IP address: %s\n", optarg);
//                    exit(EXIT_FAILURE);
//                }
//                break;
//                break;
//            case 'p':
//                payload = optarg;
//                payload_s = strlen(payload);
//                break;
//            case 's':
//                if (!(cp = strrchr(optarg, '.'))) {
//                    usage(argv[0]);
//                }
//                *cp++ = 0;
//                src_prt = (u_short) atoi(cp);
//                if ((src_ip = libnet_name2addr4(l, optarg, LIBNET_RESOLVE)) == -1) {
//                    fprintf(stderr, "Bad source IP address: %s\n", optarg);
//                    exit(EXIT_FAILURE);
//                }
//                break;
//        }
//    }
//    if (!src_ip || !src_prt || !dst_ip || !dst_prt) {
//        usage(argv[0]);
//        exit(EXIT_FAILURE);
//    }
//
//    t = libnet_build_rpc_call(
//            LIBNET_RPC_LAST_FRAG | LIBNET_RPC_CALL_TCP_H,
//            0x10e70082,
//            LIBNET_PMAP_PROGRAM,
//            2,
//            LIBNET_PMAP_PROC_DUMP,
//            0,
//            0,
//            NULL,
//            0,
//            0,
//            NULL,
//            (uint8_t *) payload,
//            payload_s,
//            l,
//            0);
//    if (t == -1) {
//        fprintf(stderr, "Can't build RPC header: %s\n", libnet_geterror(l));
//        goto bad;
//    }
//
//    t = libnet_build_tcp(
//            src_prt,                                    /* source port */
//            dst_prt,                                    /* destination port */
//            0x01010101,                                 /* sequence number */
//            0x02020202,                                 /* acknowledgement num */
//            TH_ACK,                                     /* control flags */
//            32767,                                      /* window size */
//            0,                                          /* checksum */
//            0,                                          /* urgent pointer */
//            LIBNET_TCP_H + 44 + payload_s,              /* TCP packet size */
//            NULL,                                       /* payload */
//            0,                                          /* payload size */
//            l,                                          /* libnet handle */
//            0);                                         /* libnet id */
//    if (t == -1) {
//        fprintf(stderr, "Can't build TCP header: %s\n", libnet_geterror(l));
//        goto bad;
//    }
//
//    t = libnet_build_ipv4(
//            LIBNET_IPV4_H + LIBNET_TCP_H + 44 + payload_s,/* length */
//            0,                                          /* TOS */
//            242,                                        /* IP ID */
//            0,                                          /* IP Frag */
//            64,                                         /* TTL */
//            IPPROTO_TCP,                                /* protocol */
//            0,                                          /* checksum */
//            src_ip,                                     /* source IP */
//            dst_ip,                                     /* destination IP */
//            NULL,                                       /* payload */
//            0,                                          /* payload size */
//            l,                                          /* libnet handle */
//            0);                                         /* libnet id */
//    if (t == -1) {
//        fprintf(stderr, "Can't build IP header: %s\n", libnet_geterror(l));
//        goto bad;
//    }
//
//    /*
//     *  Write it to the wire.
//     */
//    c = libnet_write(l);
//    if (c == -1) {
//        fprintf(stderr, "Write error: %s\n", libnet_geterror(l));
//        goto bad;
//    } else {
//        fprintf(stderr, "Wrote %d byte RPC TCP packet; check the wire.\n", c);
//    }
//    libnet_destroy(l);
//    return (EXIT_SUCCESS);
//    bad:
//    libnet_destroy(l);
//    return (EXIT_FAILURE);
//}
//
//
//void
//usage(char *name) {
//    fprintf(stderr,
//            "usage: %s -s source_ip.source_port -d destination_ip.destination_port"
//            " [-p payload]\n",
//            name);
//}