/*
 * This file was generated automatically by ExtUtils::ParseXS version 3.28 from the
 * contents of OID.xs. Do not edit this file, edit OID.xs instead.
 *
 *    ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "OID.xs"
/* -*- C -*- */
#if defined(_WIN32) && !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x501
#endif

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

/* pulled from Dave's, yet-to-be-used, net-snmp library rewrite.
   autocompatibility for the future? */

typedef struct netsnmp_oid_s {
    oid                 *name;
    size_t               len;
    oid                  namebuf[ MAX_OID_LEN ];
} netsnmp_oid;

static int constant(double *value, const char *name, const int len)
{
    return EINVAL;
}

netsnmp_oid *
nso_newarrayptr(oid *name, size_t name_len) 
{
    netsnmp_oid *RETVAL;
    RETVAL = malloc(sizeof(netsnmp_oid));
    RETVAL->name = RETVAL->namebuf;
    RETVAL->len = name_len;
    memcpy(RETVAL->name, name, name_len * sizeof(oid));
    return RETVAL;
}

static int __sprint_num_objid _((char *, oid *, int));

/* stolen from SNMP.xs.  Ug, this needs merging to snmplib */
/* XXX: this is only here because snmplib forces quotes around the
   data and won't return real binary data or a numeric string.  Every
   app must do its own switch() to get around it.  Ug. */
#define USE_BASIC 0
#define USE_ENUMS 1
#define USE_SPRINT_VALUE 2
static int
__snprint_value (buf, buf_len, var, tp, type, flag)
char * buf;
size_t buf_len;
netsnmp_variable_list * var;
struct tree * tp;
int type;
int flag;
{
   int len = 0;
   u_char* ip;
   struct enum_list *ep;


   buf[0] = '\0';
   if (flag == USE_SPRINT_VALUE) {
	snprint_value(buf, buf_len, var->name, var->name_length, var);
	len = strlen(buf);
   } else {
     switch (var->type) {
        case ASN_INTEGER:
           if (flag == USE_ENUMS) {
              for(ep = tp->enums; ep; ep = ep->next) {
                 if (ep->value == *var->val.integer) {
                    strcpy(buf, ep->label);
                    len = strlen(buf);
                    break;
                 }
              }
           }
           if (!len) {
              sprintf(buf,"%ld", *var->val.integer);
              len = strlen(buf);
           }
           break;

        case ASN_GAUGE:
        case ASN_COUNTER:
        case ASN_TIMETICKS:
        case ASN_UINTEGER:
           sprintf(buf,"%lu", (unsigned long) *var->val.integer);
           len = strlen(buf);
           break;

        case ASN_OCTET_STR:
        case ASN_OPAQUE:
           memcpy(buf, (char*)var->val.string, var->val_len);
           len = var->val_len;
           break;

        case ASN_IPADDRESS:
          ip = (u_char*)var->val.string;
          sprintf(buf, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
          len = strlen(buf);
          break;

        case ASN_NULL:
           break;

        case ASN_OBJECT_ID:
          __sprint_num_objid(buf, (oid *)(var->val.objid),
                             var->val_len/sizeof(oid));
          len = strlen(buf);
          break;

	case SNMP_ENDOFMIBVIEW:
          sprintf(buf,"%s", "ENDOFMIBVIEW");
	  break;
	case SNMP_NOSUCHOBJECT:
	  sprintf(buf,"%s", "NOSUCHOBJECT");
	  break;
	case SNMP_NOSUCHINSTANCE:
	  sprintf(buf,"%s", "NOSUCHINSTANCE");
	  break;

        case ASN_COUNTER64:
          printU64(buf,(struct counter64 *)var->val.counter64);
          len = strlen(buf);
          break;

        case ASN_BIT_STR:
            snprint_bitstring(buf, buf_len, var, NULL, NULL, NULL);
            len = strlen(buf);
            break;

        case ASN_NSAP:
        default:
           warn("snprint_value: asn type not handled %d\n",var->type);
     }
   }
   return(len);
}

static int
__sprint_num_objid (buf, objid, len)
char *buf;
oid *objid;
int len;
{
   int i;
   buf[0] = '\0';
   for (i=0; i < len; i++) {
	sprintf(buf,".%" NETSNMP_PRIo "u",*objid++);
	buf += strlen(buf);
   }
   return SNMPERR_SUCCESS;
}

#line 165 "OID.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef dVAR
#  define dVAR		dNOOP
#endif


/* This stuff is not part of the API! You have been warned. */
#ifndef PERL_VERSION_DECIMAL
#  define PERL_VERSION_DECIMAL(r,v,s) (r*1000000 + v*1000 + s)
#endif
#ifndef PERL_DECIMAL_VERSION
#  define PERL_DECIMAL_VERSION \
	  PERL_VERSION_DECIMAL(PERL_REVISION,PERL_VERSION,PERL_SUBVERSION)
#endif
#ifndef PERL_VERSION_GE
#  define PERL_VERSION_GE(r,v,s) \
	  (PERL_DECIMAL_VERSION >= PERL_VERSION_DECIMAL(r,v,s))
#endif
#ifndef PERL_VERSION_LE
#  define PERL_VERSION_LE(r,v,s) \
	  (PERL_DECIMAL_VERSION <= PERL_VERSION_DECIMAL(r,v,s))
#endif

/* XS_INTERNAL is the explicit static-linkage variant of the default
 * XS macro.
 *
 * XS_EXTERNAL is the same as XS_INTERNAL except it does not include
 * "STATIC", ie. it exports XSUB symbols. You probably don't want that
 * for anything but the BOOT XSUB.
 *
 * See XSUB.h in core!
 */


/* TODO: This might be compatible further back than 5.10.0. */
#if PERL_VERSION_GE(5, 10, 0) && PERL_VERSION_LE(5, 15, 1)
#  undef XS_EXTERNAL
#  undef XS_INTERNAL
#  if defined(__CYGWIN__) && defined(USE_DYNAMIC_LOADING)
#    define XS_EXTERNAL(name) __declspec(dllexport) XSPROTO(name)
#    define XS_INTERNAL(name) STATIC XSPROTO(name)
#  endif
#  if defined(__SYMBIAN32__)
#    define XS_EXTERNAL(name) EXPORT_C XSPROTO(name)
#    define XS_INTERNAL(name) EXPORT_C STATIC XSPROTO(name)
#  endif
#  ifndef XS_EXTERNAL
#    if defined(HASATTRIBUTE_UNUSED) && !defined(__cplusplus)
#      define XS_EXTERNAL(name) void name(pTHX_ CV* cv __attribute__unused__)
#      define XS_INTERNAL(name) STATIC void name(pTHX_ CV* cv __attribute__unused__)
#    else
#      ifdef __cplusplus
#        define XS_EXTERNAL(name) extern "C" XSPROTO(name)
#        define XS_INTERNAL(name) static XSPROTO(name)
#      else
#        define XS_EXTERNAL(name) XSPROTO(name)
#        define XS_INTERNAL(name) STATIC XSPROTO(name)
#      endif
#    endif
#  endif
#endif

/* perl >= 5.10.0 && perl <= 5.15.1 */


/* The XS_EXTERNAL macro is used for functions that must not be static
 * like the boot XSUB of a module. If perl didn't have an XS_EXTERNAL
 * macro defined, the best we can do is assume XS is the same.
 * Dito for XS_INTERNAL.
 */
#ifndef XS_EXTERNAL
#  define XS_EXTERNAL(name) XS(name)
#endif
#ifndef XS_INTERNAL
#  define XS_INTERNAL(name) XS(name)
#endif

/* Now, finally, after all this mess, we want an ExtUtils::ParseXS
 * internal macro that we're free to redefine for varying linkage due
 * to the EXPORT_XSUB_SYMBOLS XS keyword. This is internal, use
 * XS_EXTERNAL(name) or XS_INTERNAL(name) in your code if you need to!
 */

#undef XS_EUPXS
#if defined(PERL_EUPXS_ALWAYS_EXPORT)
#  define XS_EUPXS(name) XS_EXTERNAL(name)
#else
   /* default to internal */
#  define XS_EUPXS(name) XS_INTERNAL(name)
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
	    Perl_croak_nocontext("Usage: %s::%s(%s)", hvname, gvname, params);
        else
	    Perl_croak_nocontext("Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
	Perl_croak_nocontext("Usage: CODE(0x%"UVxf")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#define croak_xs_usage        S_croak_xs_usage

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#if PERL_VERSION_LE(5, 21, 5)
#  define newXS_deffile(a,b) Perl_newXS(aTHX_ a,b,file)
#else
#  define newXS_deffile(a,b) Perl_newXS_deffile(aTHX_ a,b)
#endif

#line 309 "OID.c"

XS_EUPXS(XS_NetSNMP__OID_newptr); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_NetSNMP__OID_newptr)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "initstring");
    {
	char *	initstring = (char *)SvPV_nolen(ST(0))
;
	netsnmp_oid *	RETVAL;
#line 161 "OID.xs"
        if (get_tree_head() == NULL)
            netsnmp_init_mib();
        RETVAL = malloc(sizeof(netsnmp_oid));
        RETVAL->name = RETVAL->namebuf;
        RETVAL->len = sizeof(RETVAL->namebuf)/sizeof(RETVAL->namebuf[0]);
        if (!snmp_parse_oid(initstring, (oid *) RETVAL->name, &RETVAL->len)) {
            snmp_log(LOG_ERR, "Can't parse: %s\n", initstring);
            RETVAL->len = 0;
            free(RETVAL);
            RETVAL = NULL;
        }
#line 333 "OID.c"
	{
	    SV * RETVALSV;
	    RETVALSV = sv_newmortal();
	    sv_setref_pv(RETVALSV, "netsnmp_oidPtr", (void*)RETVAL);
	    ST(0) = RETVALSV;
	}
    }
    XSRETURN(1);
}


XS_EUPXS(XS_NetSNMP__OID_constant); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_NetSNMP__OID_constant)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "sv");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
#line 178 "OID.xs"
	STRLEN		len;
#line 356 "OID.c"
	SV *	sv = ST(0)
;
	char *	s = SvPV(sv, len);
#line 183 "OID.xs"
        int status;
        double value;
#line 363 "OID.c"
#line 186 "OID.xs"
        value = 0;
        status = constant(&value, s, len);
        XPUSHs(sv_2mortal(newSVuv(status)));
        XPUSHs(sv_2mortal(newSVnv(value)));
#line 369 "OID.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_NetSNMP__OID__snmp_oid_compare); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_NetSNMP__OID__snmp_oid_compare)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "oid1, oid2");
    {
	netsnmp_oid *	oid1;
	netsnmp_oid *	oid2;
	int	RETVAL;
	dXSTARG;

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    oid1 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"NetSNMP::OID::_snmp_oid_compare",
			"oid1", "netsnmp_oidPtr")
;

	if (SvROK(ST(1)) && sv_derived_from(ST(1), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(1)));
	    oid2 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"NetSNMP::OID::_snmp_oid_compare",
			"oid2", "netsnmp_oidPtr")
;
#line 196 "OID.xs"
        RETVAL = snmp_oid_compare((oid *) oid1->name, oid1->len,
                                  (oid *) oid2->name, oid2->len);
#line 410 "OID.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_netsnmp_oidPtr_DESTROY); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_netsnmp_oidPtr_DESTROY)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "oid1");
    {
	netsnmp_oid *	oid1;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    oid1 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not a reference",
			"netsnmp_oidPtr::DESTROY",
			"oid1")
;
#line 207 "OID.xs"
{
    if (oid1->name != oid1->namebuf) {
	free(oid1->name);
    }
    free(oid1);
}
#line 442 "OID.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_netsnmp_oidPtr_to_string); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_netsnmp_oidPtr_to_string)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "oid1");
    {
	netsnmp_oid *	oid1;
#line 218 "OID.xs"
        static char mystr[SNMP_MAXBUF];
#line 458 "OID.c"
	char *	RETVAL;
	dXSTARG;

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    oid1 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"netsnmp_oidPtr::to_string",
			"oid1", "netsnmp_oidPtr")
;
#line 220 "OID.xs"
        {
            if (oid1->len == 0)
                snprintf(mystr, sizeof(mystr), "Illegal OID");
            else
                snprint_objid(mystr, sizeof(mystr),
                              (oid *) oid1->name, oid1->len);
            RETVAL = mystr;
        }

#line 481 "OID.c"
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_netsnmp_oidPtr_to_array); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_netsnmp_oidPtr_to_array)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "oid1");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	netsnmp_oid *	oid1;
#line 236 "OID.xs"
        int i;

#line 501 "OID.c"

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    oid1 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"netsnmp_oidPtr::to_array",
			"oid1", "netsnmp_oidPtr")
;
#line 239 "OID.xs"
        EXTEND(SP, oid1->len);
        for(i=0; i < (int)oid1->len; i++) {
            PUSHs(sv_2mortal(newSVnv(oid1->name[i])));
        }
#line 517 "OID.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_netsnmp_oidPtr_get_indexes); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_netsnmp_oidPtr_get_indexes)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "oid1");
    {
	netsnmp_oid *	oid1;
#line 248 "OID.xs"
        int i, nodecount;
        struct tree    *tp, *tpe, *tpnode, *indexnode;
        struct index_list *index;
        netsnmp_variable_list vbdata;
        char           *buf = NULL;
        size_t          buf_len = 256, out_len = 0;
        oid name[MAX_OID_LEN];
        size_t name_len = MAX_OID_LEN;
        oid *oidp;
        size_t oidp_len;
        AV *myret;
        int is_private;

#line 546 "OID.c"
	SV *	RETVAL;

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    oid1 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"netsnmp_oidPtr::get_indexes",
			"oid1", "netsnmp_oidPtr")
;
#line 262 "OID.xs"
        {
            memset(&vbdata, 0, sizeof(vbdata));
            if (NULL == (tp = get_tree(oid1->name, oid1->len,
                                       get_tree_head()))) {
                RETVAL = NULL;
                return;
            }

            if ((buf = netsnmp_malloc(buf_len)) == NULL) {
                RETVAL = NULL;
                return;
            }

            tpe = NULL;
            nodecount = 0;
            for(tpnode = tp; tpnode; tpnode = tpnode->parent) {
                nodecount++;
                if (nodecount == 2)
                    tpe = tpnode;
                if (nodecount == 3 &&
                    (strlen(tpnode->label) < 6 ||
                     strcmp(tpnode->label + strlen(tpnode->label) - 5,
                            "Table"))) {
                    /* we're not within a table.  bad logic, little choice */
                    netsnmp_free(buf);
                    RETVAL = NULL;
                    return;
                }
            }

            if (!tpe) {
                netsnmp_free(buf);
                RETVAL = NULL;
                return;
            }

            if (tpe->augments && strlen(tpe->augments) > 0) {
                /* we're augmenting another table, so use that entry instead */
                if (!snmp_parse_oid(tpe->augments, name, &name_len) ||
                    (NULL ==
                     (tpe = get_tree(name, name_len,
                                     get_tree_head())))) {
                    netsnmp_free(buf);
                    RETVAL = NULL;
                    return; /* XXX: better error recovery needed? */
                }
            }

            i = 0;
            for(index = tpe->indexes; index; index = index->next) {
                i++;
            }

            myret = (AV *) sv_2mortal((SV *) newAV());

            oidp = oid1->name + nodecount;
            oidp_len = oid1->len - nodecount;

            for(index = tpe->indexes; index; index = index->next) {
                /* XXX: NOT efficient! */
                name_len = MAX_OID_LEN;
                if (!snmp_parse_oid(index->ilabel, name, &name_len) ||
                    (NULL ==
                     (indexnode = get_tree(name, name_len,
                                           get_tree_head())))) {
                    netsnmp_free(buf);
                    RETVAL = NULL;
                    return;             /* xxx mem leak */
                }
                vbdata.type = mib_to_asn_type(indexnode->type);

                if (vbdata.type == (u_char) -1) {
                    netsnmp_free(buf);
                    RETVAL = NULL;
                    return; /* XXX: not good.  half populated stack? */
                }

                /* check for fixed length strings */
                if (vbdata.type == ASN_OCTET_STR &&
                    indexnode->ranges && !indexnode->ranges->next
                    && indexnode->ranges->low == indexnode->ranges->high) {
                    vbdata.val_len = indexnode->ranges->high;
                    vbdata.type |= ASN_PRIVATE;
                    is_private = 1;
                } else {
                    vbdata.val_len = 0;
                    if (index->isimplied) {
                        vbdata.type |= ASN_PRIVATE;
                        is_private = 1;
                    } else {
                        is_private = 0;
                    }
                }

                if (parse_one_oid_index(&oidp, &oidp_len, &vbdata, 0)
                    != SNMPERR_SUCCESS) {
                    netsnmp_free(buf);
                    RETVAL = NULL;
                    return;
                }
                out_len = 0;
                if (is_private)
                    vbdata.type ^= ASN_PRIVATE;
                out_len =
                    __snprint_value (buf, buf_len, &vbdata, indexnode,
                                     vbdata.type, 0);
/*
                sprint_realloc_value(&buf, &buf_len, &out_len,
                                     1, name, name_len, &vbdata);
*/
                snmp_free_var_internals(&vbdata);
                av_push(myret, newSVpv(buf, out_len));
            }
            netsnmp_free(buf);
            RETVAL = newRV((SV *)myret);
        }
#line 675 "OID.c"
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_netsnmp_oidPtr_append); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_netsnmp_oidPtr_append)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "oid1, string");
    {
	netsnmp_oid *	oid1;
	char *	string = (char *)SvPV_nolen(ST(1))
;
#line 386 "OID.xs"
    oid name[MAX_OID_LEN];
    size_t name_len = MAX_OID_LEN;
    int i;
#line 697 "OID.c"

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    oid1 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"netsnmp_oidPtr::append",
			"oid1", "netsnmp_oidPtr")
;
#line 390 "OID.xs"
    {
        if (!snmp_parse_oid(string, (oid *) name, &name_len)) {
            /* XXX */
        }
        if (oid1->len + name_len > MAX_OID_LEN) {
            /* XXX: illegal */
        }
        for(i = 0; i < (int)name_len; i++) {
            oid1->name[i+oid1->len] = name[i];
        }
        oid1->len += name_len;
    }
#line 721 "OID.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_netsnmp_oidPtr_append_oid); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_netsnmp_oidPtr_append_oid)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "oid1, oid2");
    {
	netsnmp_oid *	oid1;
	netsnmp_oid *	oid2;
#line 408 "OID.xs"
    int i;
#line 738 "OID.c"

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    oid1 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"netsnmp_oidPtr::append_oid",
			"oid1", "netsnmp_oidPtr")
;

	if (SvROK(ST(1)) && sv_derived_from(ST(1), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(1)));
	    oid2 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"netsnmp_oidPtr::append_oid",
			"oid2", "netsnmp_oidPtr")
;
#line 410 "OID.xs"
    {
        if (oid1->len + oid2->len > MAX_OID_LEN) {
            /* XXX: illegal */
        }
        for(i = 0; i < (int)oid2->len; i++) {
            oid1->name[i+oid1->len] = oid2->name[i];
        }
        oid1->len += oid2->len;
    }
#line 769 "OID.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_netsnmp_oidPtr_length); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_netsnmp_oidPtr_length)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "oid1");
    {
	netsnmp_oid *	oid1;
	int	RETVAL;
	dXSTARG;

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    oid1 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"netsnmp_oidPtr::length",
			"oid1", "netsnmp_oidPtr")
;
#line 424 "OID.xs"
    {
        RETVAL = oid1->len;
    }
#line 799 "OID.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_netsnmp_oidPtr_clone); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_netsnmp_oidPtr_clone)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "oid1");
    {
	netsnmp_oid *	oid1;
#line 434 "OID.xs"
    netsnmp_oid *oid2;
#line 816 "OID.c"
	netsnmp_oid *	RETVAL;

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "netsnmp_oidPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    oid1 = INT2PTR(netsnmp_oid *,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"netsnmp_oidPtr::clone",
			"oid1", "netsnmp_oidPtr")
;
#line 436 "OID.xs"
    {
        oid2 = nso_newarrayptr(oid1->name, oid1->len);
        RETVAL = oid2;
    }
#line 833 "OID.c"
	{
	    SV * RETVALSV;
	    RETVALSV = sv_newmortal();
	    sv_setref_pv(RETVALSV, "netsnmp_oidPtr", (void*)RETVAL);
	    ST(0) = RETVALSV;
	}
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS_EXTERNAL(boot_NetSNMP__OID); /* prototype to pass -Wmissing-prototypes */
XS_EXTERNAL(boot_NetSNMP__OID)
{
#if PERL_VERSION_LE(5, 21, 5)
    dVAR; dXSARGS;
#else
    dVAR; dXSBOOTARGSXSAPIVERCHK;
#endif
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(file);

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
#if PERL_VERSION_LE(5, 21, 5)
    XS_VERSION_BOOTCHECK;
#  ifdef XS_APIVERSION_BOOTCHECK
    XS_APIVERSION_BOOTCHECK;
#  endif
#endif

        (void)newXSproto_portable("NetSNMP::OID::newptr", XS_NetSNMP__OID_newptr, file, "$");
        (void)newXSproto_portable("NetSNMP::OID::constant", XS_NetSNMP__OID_constant, file, "$");
        (void)newXSproto_portable("NetSNMP::OID::_snmp_oid_compare", XS_NetSNMP__OID__snmp_oid_compare, file, "$$");
        (void)newXSproto_portable("netsnmp_oidPtr::DESTROY", XS_netsnmp_oidPtr_DESTROY, file, "$");
        (void)newXSproto_portable("netsnmp_oidPtr::to_string", XS_netsnmp_oidPtr_to_string, file, "$");
        (void)newXSproto_portable("netsnmp_oidPtr::to_array", XS_netsnmp_oidPtr_to_array, file, "$");
        (void)newXSproto_portable("netsnmp_oidPtr::get_indexes", XS_netsnmp_oidPtr_get_indexes, file, "$");
        (void)newXSproto_portable("netsnmp_oidPtr::append", XS_netsnmp_oidPtr_append, file, "$$");
        (void)newXSproto_portable("netsnmp_oidPtr::append_oid", XS_netsnmp_oidPtr_append_oid, file, "$$");
        (void)newXSproto_portable("netsnmp_oidPtr::length", XS_netsnmp_oidPtr_length, file, "$");
        (void)newXSproto_portable("netsnmp_oidPtr::clone", XS_netsnmp_oidPtr_clone, file, "$");
#if PERL_VERSION_LE(5, 21, 5)
#  if PERL_VERSION_GE(5, 9, 0)
    if (PL_unitcheckav)
        call_list(PL_scopestack_ix, PL_unitcheckav);
#  endif
    XSRETURN_YES;
#else
    Perl_xs_boot_epilog(aTHX_ ax);
#endif
}

