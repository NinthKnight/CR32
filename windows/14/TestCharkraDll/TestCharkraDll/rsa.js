var navigator = {};
function LeyBc(t) {

 var e = RSA.getPublicKey("-----BEGIN PUBLIC KEY-----MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC5gsH+AA4XWONB5TDcUd+xCz7ejOFHZKlcZDx+pF1i7Gsvi1vjyJoQhRtRSn950x498VUkx7rUxg1/ScBVfrRxQOZ8xFBye3pjAzfb22+RCuYApSVpJ3OO3KsEuKExftz9oFBv3ejxPlYc5yq7YiBO8XlTnQN0Sa4R4qhPO3I2MQIDAQAB-----END PUBLIC KEY-----");
          
      return RSA.encrypt(t, e);//感谢各位使用乐易编程网(Www.LeyBc.Com)Post Js调试工具,QQ交流群:126731209 本工具生成代码 所使用模块 含有 乐易模块和乐易V8引擎模块,各位可以在菜单的资源下载处点击下载
}
var RSA = {
    getPublicKey: function(t) {
        if (t.length < 50)
            return !1;
        if ("-----BEGIN PUBLIC KEY-----" != t.substr(0, 26))
            return !1;
        t = t.substr(26);
        if ("-----END PUBLIC KEY-----" != t.substr(t.length - 24))
            return !1;
        t = t.substr(0, t.length - 24);
        t = new ASN1Data(Base64.decode(t));
        if (t.error)
            return !1;
        t = t.data;
        if ("1.2.840.113549.1.1.1" == t[0][0][0])
            return new RSAPublicKey(t[0][1][0][0],t[0][1][0][1]);
        else
            return !1
    },
    encrypt: function(t/*明文*/, e/* RSA公钥 */) {
        if (!e)
            return !1;
        var i = e.modulus.bitLength() + 7 >> 3;
        t = this.pkcs1pad2(t, i);
        if (!t)
            return !1;
        t = t.modPowInt(e.encryptionExponent, e.modulus);
        if (!t)
            return !1;
        t = t.toString(16);
        for (; t.length < 2 * i; )
            t = "0" + t;
        return Base64.encode(Hex.decode(t))
    },
    decrypt: function(t) {
        var e = new BigInteger(t,16)
    },
    pkcs1pad2: function(t, e) {
        if (e < t.length + 11)
            return null;
        var i = [];
        var n = t.length - 1;
        for (; n >= 0 && e > 0; )
            i[--e] = t.charCodeAt(n--);
        i[--e] = 0;
        for (; e > 2; )
            i[--e] = Math.floor(254 * Math.random()) + 1;
        i[--e] = 2;
        i[--e] = 0;
        return new BigInteger(i)
    }
};
 var ASN1Data = function(t) {
    this.error = !1;
    this.parse = function(t) {
        if (!t) {
            this.error = !0;
            return null
        }
        var e = [];
        for (; t.length > 0; ) {
            var i = t.charCodeAt(0);
            t = t.substr(1);
            var n = 0;
            if (5 == (31 & i))
                t = t.substr(1);
            else if (128 & t.charCodeAt(0)) {
                var r = 127 & t.charCodeAt(0);
                t = t.substr(1);
                if (r > 0)
                    n = t.charCodeAt(0);
                if (r > 1)
                    n = n << 8 | t.charCodeAt(1);
                if (r > 2) {
                    this.error = !0;
                    return null
                }
                t = t.substr(r)
            } else {
                n = t.charCodeAt(0);
                t = t.substr(1)
            }
            var s = "";
            if (n) {
                if (n > t.length) {
                    this.error = !0;
                    return null
                }
                s = t.substr(0, n);
                t = t.substr(n)
            }
            if (32 & i)
                e.push(this.parse(s));
            else
                e.push(this.value(128 & i ? 4 : 31 & i, s))
        }
        return e
    }
    ;
    this.value = function(t, e) {
        if (1 == t)
            return e ? !0 : !1;
        else if (2 == t)
            return e;
        else if (3 == t)
            return this.parse(e.substr(1));
        else if (5 == t)
            return null;
        else if (6 == t) {
            var i = [];
            var n = e.charCodeAt(0);
            i.push(Math.floor(n / 40));
            i.push(n - 40 * i[0]);
            var r = [];
            var s = 0;
            var o;
            for (o = 1; o < e.length; o++) {
                var a = e.charCodeAt(o);
                r.push(127 & a);
                if (128 & a)
                    s++;
                else {
                    var _;
                    var c = 0;
                    for (_ = 0; _ < r.length; _++)
                        c += r[_] * Math.pow(128, s--);
                    i.push(c);
                    s = 0;
                    r = []
                }
            }
            return i.join(".")
        }
        return null
    }
    ;
    this.data = this.parse(t)
};
var Base64 = {
    base64: "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",
    encode: function(t) {
        if (!t)
            return !1;
        var e = "";
        var i, n, r;
        var s, o, a, _;
        var c = 0;
        do {
            i = t.charCodeAt(c++);
            n = t.charCodeAt(c++);
            r = t.charCodeAt(c++);
            s = i >> 2;
            o = (3 & i) << 4 | n >> 4;
            a = (15 & n) << 2 | r >> 6;
            _ = 63 & r;
            if (isNaN(n))
                a = _ = 64;
            else if (isNaN(r))
                _ = 64;
            e += this.base64.charAt(s) + this.base64.charAt(o) + this.base64.charAt(a) + this.base64.charAt(_)
        } while (c < t.length);return e
    },
    decode: function(t) {
        if (!t)
            return !1;
        t = t.replace(/[^A-Za-z0-9\+\/\=]/g, "");
        var e = "";
        var i, n, r, s;
        var o = 0;
        do {
            i = this.base64.indexOf(t.charAt(o++));
            n = this.base64.indexOf(t.charAt(o++));
            r = this.base64.indexOf(t.charAt(o++));
            s = this.base64.indexOf(t.charAt(o++));
            e += String.fromCharCode(i << 2 | n >> 4);
            if (64 != r)
                e += String.fromCharCode((15 & n) << 4 | r >> 2);
            if (64 != s)
                e += String.fromCharCode((3 & r) << 6 | s)
        } while (o < t.length);return e
    }
};
var RSAPublicKey = function(t, e) {
    this.modulus = new BigInteger(Hex.encode(t),16);
    this.encryptionExponent = new BigInteger(Hex.encode(e),16)
};
var dbits;
var canary = 0xdeadbeefcafe;
var j_lm = 15715070 == (16777215 & canary);
function BigInteger(t, e, i) {
    if (null != t)
        if ("number" == typeof t)
            this.fromNumber(t, e, i);
        else if (null == e && "string" != typeof t)
            this.fromString(t, 256);
        else
            this.fromString(t, e)
}
function nbi() {
    return new BigInteger(null)
}
function am1(t, e, i, n, r, s) {
    for (; --s >= 0; ) {
        var o = e * this[t++] + i[n] + r;
        r = Math.floor(o / 67108864);
        i[n++] = 67108863 & o
    }
    return r
}
function am2(t, e, i, n, r, s) {
    var o = 32767 & e
      , a = e >> 15;
    for (; --s >= 0; ) {
        var _ = 32767 & this[t];
        var c = this[t++] >> 15;
        var h = a * _ + c * o;
        _ = o * _ + ((32767 & h) << 15) + i[n] + (1073741823 & r);
        r = (_ >>> 30) + (h >>> 15) + a * c + (r >>> 30);
        i[n++] = 1073741823 & _
    }
    return r
}
function am3(t, e, i, n, r, s) {
    var o = 16383 & e
      , a = e >> 14;
    for (; --s >= 0; ) {
        var _ = 16383 & this[t];
        var c = this[t++] >> 14;
        var h = a * _ + c * o;
        _ = o * _ + ((16383 & h) << 14) + i[n] + r;
        r = (_ >> 28) + (h >> 14) + a * c;
        i[n++] = 268435455 & _
    }
    return r
}
if (j_lm && "Microsoft Internet Explorer" == navigator.appName) {
    BigInteger.prototype.am = am2;
    dbits = 30
} else if (j_lm && "Netscape" != navigator.appName) {
    BigInteger.prototype.am = am1;
    dbits = 26
} else {
    BigInteger.prototype.am = am3;
    dbits = 28
}
BigInteger.prototype.DB = dbits;
BigInteger.prototype.DM = (1 << dbits) - 1;
BigInteger.prototype.DV = 1 << dbits;
var BI_FP = 52;
BigInteger.prototype.FV = Math.pow(2, BI_FP);
BigInteger.prototype.F1 = BI_FP - dbits;
BigInteger.prototype.F2 = 2 * dbits - BI_FP;
var BI_RM = "0123456789abcdefghijklmnopqrstuvwxyz";
var BI_RC = new Array;
var rr, vv;
rr = "0".charCodeAt(0);
for (vv = 0; vv <= 9; ++vv)
    BI_RC[rr++] = vv;
rr = "a".charCodeAt(0);
for (vv = 10; vv < 36; ++vv)
    BI_RC[rr++] = vv;
rr = "A".charCodeAt(0);
for (vv = 10; vv < 36; ++vv)
    BI_RC[rr++] = vv;
function int2char(t) {
    return BI_RM.charAt(t)
}
function intAt(t, e) {
    var i = BI_RC[t.charCodeAt(e)];
    return null == i ? -1 : i
}
function bnpCopyTo(t) {
    for (var e = this.t - 1; e >= 0; --e)
        t[e] = this[e];
    t.t = this.t;
    t.s = this.s
}
function bnpFromInt(t) {
    this.t = 1;
    this.s = t < 0 ? -1 : 0;
    if (t > 0)
        this[0] = t;
    else if (t < -1)
        this[0] = t + DV;
    else
        this.t = 0
}
function nbv(t) {
    var e = nbi();
    e.fromInt(t);
    return e
}
function bnpFromString(t, e) {
    var i;
    if (16 == e)
        i = 4;
    else if (8 == e)
        i = 3;
    else if (256 == e)
        i = 8;
    else if (2 == e)
        i = 1;
    else if (32 == e)
        i = 5;
    else if (4 == e)
        i = 2;
    else {
        this.fromRadix(t, e);
        return
    }
    this.t = 0;
    this.s = 0;
    var n = t.length
      , r = !1
      , s = 0;
    for (; --n >= 0; ) {
        var o = 8 == i ? 255 & t[n] : intAt(t, n);
        if (!(o < 0)) {
            r = !1;
            if (0 == s)
                this[this.t++] = o;
            else if (s + i > this.DB) {
                this[this.t - 1] |= (o & (1 << this.DB - s) - 1) << s;
                this[this.t++] = o >> this.DB - s
            } else
                this[this.t - 1] |= o << s;
            s += i;
            if (s >= this.DB)
                s -= this.DB
        } else if ("-" == t.charAt(n))
            r = !0
    }
    if (8 == i && 0 != (128 & t[0])) {
        this.s = -1;
        if (s > 0)
            this[this.t - 1] |= (1 << this.DB - s) - 1 << s
    }
    this.clamp();
    if (r)
        BigInteger.ZERO.subTo(this, this)
}
function bnpClamp() {
    var t = this.s & this.DM;
    for (; this.t > 0 && this[this.t - 1] == t; )
        --this.t
}
function bnToString(t) {
    if (this.s < 0)
        return "-" + this.negate().toString(t);
    var e;
    if (16 == t)
        e = 4;
    else if (8 == t)
        e = 3;
    else if (2 == t)
        e = 1;
    else if (32 == t)
        e = 5;
    else if (4 == t)
        e = 2;
    else
        return this.toRadix(t);
    var i = (1 << e) - 1, n, r = !1, s = "", o = this.t;
    var a = this.DB - o * this.DB % e;
    if (o-- > 0) {
        if (a < this.DB && (n = this[o] >> a) > 0) {
            r = !0;
            s = int2char(n)
        }
        for (; o >= 0; ) {
            if (a < e) {
                n = (this[o] & (1 << a) - 1) << e - a;
                n |= this[--o] >> (a += this.DB - e)
            } else {
                n = this[o] >> (a -= e) & i;
                if (a <= 0) {
                    a += this.DB;
                    --o
                }
            }
            if (n > 0)
                r = !0;
            if (r)
                s += int2char(n)
        }
    }
    return r ? s : "0"
}
function bnNegate() {
    var t = nbi();
    BigInteger.ZERO.subTo(this, t);
    return t
}
function bnAbs() {
    return this.s < 0 ? this.negate() : this
}
function bnCompareTo(t) {
    var e = this.s - t.s;
    if (0 != e)
        return e;
    var i = this.t;
    e = i - t.t;
    if (0 != e)
        return this.s < 0 ? -e : e;
    for (; --i >= 0; )
        if (0 != (e = this[i] - t[i]))
            return e;
    return 0
}
function nbits(t) {
    var e = 1, i;
    if (0 != (i = t >>> 16)) {
        t = i;
        e += 16
    }
    if (0 != (i = t >> 8)) {
        t = i;
        e += 8
    }
    if (0 != (i = t >> 4)) {
        t = i;
        e += 4
    }
    if (0 != (i = t >> 2)) {
        t = i;
        e += 2
    }
    if (0 != (i = t >> 1)) {
        t = i;
        e += 1
    }
    return e
}
function bnBitLength() {
    if (this.t <= 0)
        return 0;
    else
        return this.DB * (this.t - 1) + nbits(this[this.t - 1] ^ this.s & this.DM)
}
function bnpDLShiftTo(t, e) {
    var i;
    for (i = this.t - 1; i >= 0; --i)
        e[i + t] = this[i];
    for (i = t - 1; i >= 0; --i)
        e[i] = 0;
    e.t = this.t + t;
    e.s = this.s
}
function bnpDRShiftTo(t, e) {
    for (var i = t; i < this.t; ++i)
        e[i - t] = this[i];
    e.t = Math.max(this.t - t, 0);
    e.s = this.s
}
function bnpLShiftTo(t, e) {
    var i = t % this.DB;
    var n = this.DB - i;
    var r = (1 << n) - 1;
    var s = Math.floor(t / this.DB), o = this.s << i & this.DM, a;
    for (a = this.t - 1; a >= 0; --a) {
        e[a + s + 1] = this[a] >> n | o;
        o = (this[a] & r) << i
    }
    for (a = s - 1; a >= 0; --a)
        e[a] = 0;
    e[s] = o;
    e.t = this.t + s + 1;
    e.s = this.s;
    e.clamp()
}
function bnpRShiftTo(t, e) {
    e.s = this.s;
    var i = Math.floor(t / this.DB);
    if (!(i >= this.t)) {
        var n = t % this.DB;
        var r = this.DB - n;
        var s = (1 << n) - 1;
        e[0] = this[i] >> n;
        for (var o = i + 1; o < this.t; ++o) {
            e[o - i - 1] |= (this[o] & s) << r;
            e[o - i] = this[o] >> n
        }
        if (n > 0)
            e[this.t - i - 1] |= (this.s & s) << r;
        e.t = this.t - i;
        e.clamp()
    } else
        e.t = 0
}
function bnpSubTo(t, e) {
    var i = 0
      , n = 0
      , r = Math.min(t.t, this.t);
    for (; i < r; ) {
        n += this[i] - t[i];
        e[i++] = n & this.DM;
        n >>= this.DB
    }
    if (t.t < this.t) {
        n -= t.s;
        for (; i < this.t; ) {
            n += this[i];
            e[i++] = n & this.DM;
            n >>= this.DB
        }
        n += this.s
    } else {
        n += this.s;
        for (; i < t.t; ) {
            n -= t[i];
            e[i++] = n & this.DM;
            n >>= this.DB
        }
        n -= t.s
    }
    e.s = n < 0 ? -1 : 0;
    if (n < -1)
        e[i++] = this.DV + n;
    else if (n > 0)
        e[i++] = n;
    e.t = i;
    e.clamp()
}
function bnpMultiplyTo(t, e) {
    var i = this.abs()
      , n = t.abs();
    var r = i.t;
    e.t = r + n.t;
    for (; --r >= 0; )
        e[r] = 0;
    for (r = 0; r < n.t; ++r)
        e[r + i.t] = i.am(0, n[r], e, r, 0, i.t);
    e.s = 0;
    e.clamp();
    if (this.s != t.s)
        BigInteger.ZERO.subTo(e, e)
}
function bnpSquareTo(t) {
    var e = this.abs();
    var i = t.t = 2 * e.t;
    for (; --i >= 0; )
        t[i] = 0;
    for (i = 0; i < e.t - 1; ++i) {
        var n = e.am(i, e[i], t, 2 * i, 0, 1);
        if ((t[i + e.t] += e.am(i + 1, 2 * e[i], t, 2 * i + 1, n, e.t - i - 1)) >= e.DV) {
            t[i + e.t] -= e.DV;
            t[i + e.t + 1] = 1
        }
    }
    if (t.t > 0)
        t[t.t - 1] += e.am(i, e[i], t, 2 * i, 0, 1);
    t.s = 0;
    t.clamp()
}
function bnpDivRemTo(t, e, i) {
    var n = t.abs();
    if (!(n.t <= 0)) {
        var r = this.abs();
        if (!(r.t < n.t)) {
            if (null == i)
                i = nbi();
            var s = nbi()
              , o = this.s
              , a = t.s;
            var _ = this.DB - nbits(n[n.t - 1]);
            if (_ > 0) {
                n.lShiftTo(_, s);
                r.lShiftTo(_, i)
            } else {
                n.copyTo(s);
                r.copyTo(i)
            }
            var c = s.t;
            var h = s[c - 1];
            if (0 != h) {
                var u = h * (1 << this.F1) + (c > 1 ? s[c - 2] >> this.F2 : 0);
                var l = this.FV / u
                  , d = (1 << this.F1) / u
                  , f = 1 << this.F2;
                var m = i.t
                  , p = m - c
                  , g = null == e ? nbi() : e;
                s.dlShiftTo(p, g);
                if (i.compareTo(g) >= 0) {
                    i[i.t++] = 1;
                    i.subTo(g, i)
                }
                BigInteger.ONE.dlShiftTo(c, g);
                g.subTo(s, s);
                for (; s.t < c; )
                    s[s.t++] = 0;
                for (; --p >= 0; ) {
                    var v = i[--m] == h ? this.DM : Math.floor(i[m] * l + (i[m - 1] + f) * d);
                    if ((i[m] += s.am(0, v, i, p, 0, c)) < v) {
                        s.dlShiftTo(p, g);
                        i.subTo(g, i);
                        for (; i[m] < --v; )
                            i.subTo(g, i)
                    }
                }
                if (null != e) {
                    i.drShiftTo(c, e);
                    if (o != a)
                        BigInteger.ZERO.subTo(e, e)
                }
                i.t = c;
                i.clamp();
                if (_ > 0)
                    i.rShiftTo(_, i);
                if (o < 0)
                    BigInteger.ZERO.subTo(i, i)
            }
        } else {
            if (null != e)
                e.fromInt(0);
            if (null != i)
                this.copyTo(i)
        }
    }
}
function bnMod(t) {
    var e = nbi();
    this.abs().divRemTo(t, null, e);
    if (this.s < 0 && e.compareTo(BigInteger.ZERO) > 0)
        t.subTo(e, e);
    return e
}
function Classic(t) {
    this.m = t
}
function cConvert(t) {
    if (t.s < 0 || t.compareTo(this.m) >= 0)
        return t.mod(this.m);
    else
        return t
}
function cRevert(t) {
    return t
}
function cReduce(t) {
    t.divRemTo(this.m, null, t)
}
function cMulTo(t, e, i) {
    t.multiplyTo(e, i);
    this.reduce(i)
}
function cSqrTo(t, e) {
    t.squareTo(e);
    this.reduce(e)
}
Classic.prototype.convert = cConvert;
Classic.prototype.revert = cRevert;
Classic.prototype.reduce = cReduce;
Classic.prototype.mulTo = cMulTo;
Classic.prototype.sqrTo = cSqrTo;
function bnpInvDigit() {
    if (this.t < 1)
        return 0;
    var t = this[0];
    if (0 == (1 & t))
        return 0;
    var e = 3 & t;
    e = e * (2 - (15 & t) * e) & 15;
    e = e * (2 - (255 & t) * e) & 255;
    e = e * (2 - ((65535 & t) * e & 65535)) & 65535;
    e = e * (2 - t * e % this.DV) % this.DV;
    return e > 0 ? this.DV - e : -e
}
function Montgomery(t) {
    this.m = t;
    this.mp = t.invDigit();
    this.mpl = 32767 & this.mp;
    this.mph = this.mp >> 15;
    this.um = (1 << t.DB - 15) - 1;
    this.mt2 = 2 * t.t
}
function montConvert(t) {
    var e = nbi();
    t.abs().dlShiftTo(this.m.t, e);
    e.divRemTo(this.m, null, e);
    if (t.s < 0 && e.compareTo(BigInteger.ZERO) > 0)
        this.m.subTo(e, e);
    return e
}
function montRevert(t) {
    var e = nbi();
    t.copyTo(e);
    this.reduce(e);
    return e
}
function montReduce(t) {
    for (; t.t <= this.mt2; )
        t[t.t++] = 0;
    for (var e = 0; e < this.m.t; ++e) {
        var i = 32767 & t[e];
        var n = i * this.mpl + ((i * this.mph + (t[e] >> 15) * this.mpl & this.um) << 15) & t.DM;
        i = e + this.m.t;
        t[i] += this.m.am(0, n, t, e, 0, this.m.t);
        for (; t[i] >= t.DV; ) {
            t[i] -= t.DV;
            t[++i]++
        }
    }
    t.clamp();
    t.drShiftTo(this.m.t, t);
    if (t.compareTo(this.m) >= 0)
        t.subTo(this.m, t)
}
function montSqrTo(t, e) {
    t.squareTo(e);
    this.reduce(e)
}
function montMulTo(t, e, i) {
    t.multiplyTo(e, i);
    this.reduce(i)
}
Montgomery.prototype.convert = montConvert;
Montgomery.prototype.revert = montRevert;
Montgomery.prototype.reduce = montReduce;
Montgomery.prototype.mulTo = montMulTo;
Montgomery.prototype.sqrTo = montSqrTo;
function bnpIsEven() {
    return 0 == (this.t > 0 ? 1 & this[0] : this.s)
}
function bnpExp(t, e) {
    if (t > 4294967295 || t < 1)
        return BigInteger.ONE;
    var i = nbi()
      , n = nbi()
      , r = e.convert(this)
      , s = nbits(t) - 1;
    r.copyTo(i);
    for (; --s >= 0; ) {
        e.sqrTo(i, n);
        if ((t & 1 << s) > 0)
            e.mulTo(n, r, i);
        else {
            var o = i;
            i = n;
            n = o
        }
    }
    return e.revert(i)
}
function bnModPowInt(t, e) {
    var i;
    if (t < 256 || e.isEven())
        i = new Classic(e);
    else
        i = new Montgomery(e);
    return this.exp(t, i)
}
BigInteger.prototype.copyTo = bnpCopyTo;
BigInteger.prototype.fromInt = bnpFromInt;
BigInteger.prototype.fromString = bnpFromString;
BigInteger.prototype.clamp = bnpClamp;
BigInteger.prototype.dlShiftTo = bnpDLShiftTo;
BigInteger.prototype.drShiftTo = bnpDRShiftTo;
BigInteger.prototype.lShiftTo = bnpLShiftTo;
BigInteger.prototype.rShiftTo = bnpRShiftTo;
BigInteger.prototype.subTo = bnpSubTo;
BigInteger.prototype.multiplyTo = bnpMultiplyTo;
BigInteger.prototype.squareTo = bnpSquareTo;
BigInteger.prototype.divRemTo = bnpDivRemTo;
BigInteger.prototype.invDigit = bnpInvDigit;
BigInteger.prototype.isEven = bnpIsEven;
BigInteger.prototype.exp = bnpExp;
BigInteger.prototype.toString = bnToString;
BigInteger.prototype.negate = bnNegate;
BigInteger.prototype.abs = bnAbs;
BigInteger.prototype.compareTo = bnCompareTo;
BigInteger.prototype.bitLength = bnBitLength;
BigInteger.prototype.mod = bnMod;
BigInteger.prototype.modPowInt = bnModPowInt;
BigInteger.ZERO = nbv(0);
BigInteger.ONE = nbv(1);
function bnClone() {
    var t = nbi();
    this.copyTo(t);
    return t
}
function bnIntValue() {
    if (this.s < 0) {
        if (1 == this.t)
            return this[0] - this.DV;
        else if (0 == this.t)
            return -1
    } else if (1 == this.t)
        return this[0];
    else if (0 == this.t)
        return 0;
    return (this[1] & (1 << 32 - this.DB) - 1) << this.DB | this[0]
}
function bnByteValue() {
    return 0 == this.t ? this.s : this[0] << 24 >> 24
}
function bnShortValue() {
    return 0 == this.t ? this.s : this[0] << 16 >> 16
}
function bnpChunkSize(t) {
    return Math.floor(Math.LN2 * this.DB / Math.log(t))
}
function bnSigNum() {
    if (this.s < 0)
        return -1;
    else if (this.t <= 0 || 1 == this.t && this[0] <= 0)
        return 0;
    else
        return 1
}
function bnpToRadix(t) {
    if (null == t)
        t = 10;
    if (0 == this.signum() || t < 2 || t > 36)
        return "0";
    var e = this.chunkSize(t);
    var i = Math.pow(t, e);
    var n = nbv(i)
      , r = nbi()
      , s = nbi()
      , o = "";
    this.divRemTo(n, r, s);
    for (; r.signum() > 0; ) {
        o = (i + s.intValue()).toString(t).substr(1) + o;
        r.divRemTo(n, r, s)
    }
    return s.intValue().toString(t) + o
}
function bnpFromRadix(t, e) {
    this.fromInt(0);
    if (null == e)
        e = 10;
    var i = this.chunkSize(e);
    var n = Math.pow(e, i)
      , r = !1
      , s = 0
      , o = 0;
    for (var a = 0; a < t.length; ++a) {
        var _ = intAt(t, a);
        if (!(_ < 0)) {
            o = e * o + _;
            if (++s >= i) {
                this.dMultiply(n);
                this.dAddOffset(o, 0);
                s = 0;
                o = 0
            }
        } else if ("-" == t.charAt(a) && 0 == this.signum())
            r = !0
    }
    if (s > 0) {
        this.dMultiply(Math.pow(e, s));
        this.dAddOffset(o, 0)
    }
    if (r)
        BigInteger.ZERO.subTo(this, this)
}
function bnpFromNumber(t, e, i) {
    if ("number" == typeof e)
        if (t < 2)
            this.fromInt(1);
        else {
            this.fromNumber(t, i);
            if (!this.testBit(t - 1))
                this.bitwiseTo(BigInteger.ONE.shiftLeft(t - 1), op_or, this);
            if (this.isEven())
                this.dAddOffset(1, 0);
            for (; !this.isProbablePrime(e); ) {
                this.dAddOffset(2, 0);
                if (this.bitLength() > t)
                    this.subTo(BigInteger.ONE.shiftLeft(t - 1), this)
            }
        }
    else {
        var n = new Array
          , r = 7 & t;
        n.length = (t >> 3) + 1;
        e.nextBytes(n);
        if (r > 0)
            n[0] &= (1 << r) - 1;
        else
            n[0] = 0;
        this.fromString(n, 256)
    }
}
function bnToByteArray() {
    var t = this.t
      , e = new Array;
    e[0] = this.s;
    var i = this.DB - t * this.DB % 8, n, r = 0;
    if (t-- > 0) {
        if (i < this.DB && (n = this[t] >> i) != (this.s & this.DM) >> i)
            e[r++] = n | this.s << this.DB - i;
        for (; t >= 0; ) {
            if (i < 8) {
                n = (this[t] & (1 << i) - 1) << 8 - i;
                n |= this[--t] >> (i += this.DB - 8)
            } else {
                n = this[t] >> (i -= 8) & 255;
                if (i <= 0) {
                    i += this.DB;
                    --t
                }
            }
            if (0 != (128 & n))
                n |= -256;
            if (0 == r && (128 & this.s) != (128 & n))
                ++r;
            if (r > 0 || n != this.s)
                e[r++] = n
        }
    }
    return e
}
function bnEquals(t) {
    return 0 == this.compareTo(t)
}
function bnMin(t) {
    return this.compareTo(t) < 0 ? this : t
}
function bnMax(t) {
    return this.compareTo(t) > 0 ? this : t
}
function bnpBitwiseTo(t, e, i) {
    var n, r, s = Math.min(t.t, this.t);
    for (n = 0; n < s; ++n)
        i[n] = e(this[n], t[n]);
    if (t.t < this.t) {
        r = t.s & this.DM;
        for (n = s; n < this.t; ++n)
            i[n] = e(this[n], r);
        i.t = this.t
    } else {
        r = this.s & this.DM;
        for (n = s; n < t.t; ++n)
            i[n] = e(r, t[n]);
        i.t = t.t
    }
    i.s = e(this.s, t.s);
    i.clamp()
}
function op_and(t, e) {
    return t & e
}
function bnAnd(t) {
    var e = nbi();
    this.bitwiseTo(t, op_and, e);
    return e
}
function op_or(t, e) {
    return t | e
}
function bnOr(t) {
    var e = nbi();
    this.bitwiseTo(t, op_or, e);
    return e
}
function op_xor(t, e) {
    return t ^ e
}
function bnXor(t) {
    var e = nbi();
    this.bitwiseTo(t, op_xor, e);
    return e
}
function op_andnot(t, e) {
    return t & ~e
}
function bnAndNot(t) {
    var e = nbi();
    this.bitwiseTo(t, op_andnot, e);
    return e
}
function bnNot() {
    var t = nbi();
    for (var e = 0; e < this.t; ++e)
        t[e] = this.DM & ~this[e];
    t.t = this.t;
    t.s = ~this.s;
    return t
}
function bnShiftLeft(t) {
    var e = nbi();
    if (t < 0)
        this.rShiftTo(-t, e);
    else
        this.lShiftTo(t, e);
    return e
}
function bnShiftRight(t) {
    var e = nbi();
    if (t < 0)
        this.lShiftTo(-t, e);
    else
        this.rShiftTo(t, e);
    return e
}
function lbit(t) {
    if (0 == t)
        return -1;
    var e = 0;
    if (0 == (65535 & t)) {
        t >>= 16;
        e += 16
    }
    if (0 == (255 & t)) {
        t >>= 8;
        e += 8
    }
    if (0 == (15 & t)) {
        t >>= 4;
        e += 4
    }
    if (0 == (3 & t)) {
        t >>= 2;
        e += 2
    }
    if (0 == (1 & t))
        ++e;
    return e
}
function bnGetLowestSetBit() {
    for (var t = 0; t < this.t; ++t)
        if (0 != this[t])
            return t * this.DB + lbit(this[t]);
    if (this.s < 0)
        return this.t * this.DB;
    else
        return -1
}
function cbit(t) {
    var e = 0;
    for (; 0 != t; ) {
        t &= t - 1;
        ++e
    }
    return e
}
function bnBitCount() {
    var t = 0
      , e = this.s & this.DM;
    for (var i = 0; i < this.t; ++i)
        t += cbit(this[i] ^ e);
    return t
}
function bnTestBit(t) {
    var e = Math.floor(t / this.DB);
    if (e >= this.t)
        return 0 != this.s;
    else
        return 0 != (this[e] & 1 << t % this.DB)
}
function bnpChangeBit(t, e) {
    var i = BigInteger.ONE.shiftLeft(t);
    this.bitwiseTo(i, e, i);
    return i
}
function bnSetBit(t) {
    return this.changeBit(t, op_or)
}
function bnClearBit(t) {
    return this.changeBit(t, op_andnot)
}
function bnFlipBit(t) {
    return this.changeBit(t, op_xor)
}
function bnpAddTo(t, e) {
    var i = 0
      , n = 0
      , r = Math.min(t.t, this.t);
    for (; i < r; ) {
        n += this[i] + t[i];
        e[i++] = n & this.DM;
        n >>= this.DB
    }
    if (t.t < this.t) {
        n += t.s;
        for (; i < this.t; ) {
            n += this[i];
            e[i++] = n & this.DM;
            n >>= this.DB
        }
        n += this.s
    } else {
        n += this.s;
        for (; i < t.t; ) {
            n += t[i];
            e[i++] = n & this.DM;
            n >>= this.DB
        }
        n += t.s
    }
    e.s = n < 0 ? -1 : 0;
    if (n > 0)
        e[i++] = n;
    else if (n < -1)
        e[i++] = this.DV + n;
    e.t = i;
    e.clamp()
}
function bnAdd(t) {
    var e = nbi();
    this.addTo(t, e);
    return e
}
function bnSubtract(t) {
    var e = nbi();
    this.subTo(t, e);
    return e
}
function bnMultiply(t) {
    var e = nbi();
    this.multiplyTo(t, e);
    return e
}
function bnSquare() {
    var t = nbi();
    this.squareTo(t);
    return t
}
function bnDivide(t) {
    var e = nbi();
    this.divRemTo(t, e, null);
    return e
}
function bnRemainder(t) {
    var e = nbi();
    this.divRemTo(t, null, e);
    return e
}
function bnDivideAndRemainder(t) {
    var e = nbi()
      , i = nbi();
    this.divRemTo(t, e, i);
    return new Array(e,i)
}
function bnpDMultiply(t) {
    this[this.t] = this.am(0, t - 1, this, 0, 0, this.t);
    ++this.t;
    this.clamp()
}
function bnpDAddOffset(t, e) {
    if (0 != t) {
        for (; this.t <= e; )
            this[this.t++] = 0;
        this[e] += t;
        for (; this[e] >= this.DV; ) {
            this[e] -= this.DV;
            if (++e >= this.t)
                this[this.t++] = 0;
            ++this[e]
        }
    }
}
function NullExp() {}
function nNop(t) {
    return t
}
function nMulTo(t, e, i) {
    t.multiplyTo(e, i)
}
function nSqrTo(t, e) {
    t.squareTo(e)
}
NullExp.prototype.convert = nNop;
NullExp.prototype.revert = nNop;
NullExp.prototype.mulTo = nMulTo;
NullExp.prototype.sqrTo = nSqrTo;
function bnPow(t) {
    return this.exp(t, new NullExp)
}
function bnpMultiplyLowerTo(t, e, i) {
    var n = Math.min(this.t + t.t, e);
    i.s = 0;
    i.t = n;
    for (; n > 0; )
        i[--n] = 0;
    var r;
    for (r = i.t - this.t; n < r; ++n)
        i[n + this.t] = this.am(0, t[n], i, n, 0, this.t);
    for (r = Math.min(t.t, e); n < r; ++n)
        this.am(0, t[n], i, n, 0, e - n);
    i.clamp()
}
function bnpMultiplyUpperTo(t, e, i) {
    --e;
    var n = i.t = this.t + t.t - e;
    i.s = 0;
    for (; --n >= 0; )
        i[n] = 0;
    for (n = Math.max(e - this.t, 0); n < t.t; ++n)
        i[this.t + n - e] = this.am(e - n, t[n], i, 0, 0, this.t + n - e);
    i.clamp();
    i.drShiftTo(1, i)
}
function Barrett(t) {
    this.r2 = nbi();
    this.q3 = nbi();
    BigInteger.ONE.dlShiftTo(2 * t.t, this.r2);
    this.mu = this.r2.divide(t);
    this.m = t
}
function barrettConvert(t) {
    if (t.s < 0 || t.t > 2 * this.m.t)
        return t.mod(this.m);
    else if (t.compareTo(this.m) < 0)
        return t;
    else {
        var e = nbi();
        t.copyTo(e);
        this.reduce(e);
        return e
    }
}
function barrettRevert(t) {
    return t
}
function barrettReduce(t) {
    t.drShiftTo(this.m.t - 1, this.r2);
    if (t.t > this.m.t + 1) {
        t.t = this.m.t + 1;
        t.clamp()
    }
    this.mu.multiplyUpperTo(this.r2, this.m.t + 1, this.q3);
    this.m.multiplyLowerTo(this.q3, this.m.t + 1, this.r2);
    for (; t.compareTo(this.r2) < 0; )
        t.dAddOffset(1, this.m.t + 1);
    t.subTo(this.r2, t);
    for (; t.compareTo(this.m) >= 0; )
        t.subTo(this.m, t)
}
function barrettSqrTo(t, e) {
    t.squareTo(e);
    this.reduce(e)
}
function barrettMulTo(t, e, i) {
    t.multiplyTo(e, i);
    this.reduce(i)
}
Barrett.prototype.convert = barrettConvert;
Barrett.prototype.revert = barrettRevert;
Barrett.prototype.reduce = barrettReduce;
Barrett.prototype.mulTo = barrettMulTo;
Barrett.prototype.sqrTo = barrettSqrTo;
function bnModPow(t, e) {
    var i = t.bitLength(), n, r = nbv(1), s;
    if (i <= 0)
        return r;
    else if (i < 18)
        n = 1;
    else if (i < 48)
        n = 3;
    else if (i < 144)
        n = 4;
    else if (i < 768)
        n = 5;
    else
        n = 6;
    if (i < 8)
        s = new Classic(e);
    else if (e.isEven())
        s = new Barrett(e);
    else
        s = new Montgomery(e);
    var o = new Array
      , a = 3
      , _ = n - 1
      , c = (1 << n) - 1;
    o[1] = s.convert(this);
    if (n > 1) {
        var h = nbi();
        s.sqrTo(o[1], h);
        for (; a <= c; ) {
            o[a] = nbi();
            s.mulTo(h, o[a - 2], o[a]);
            a += 2
        }
    }
    var u = t.t - 1, l, d = !0, f = nbi(), m;
    i = nbits(t[u]) - 1;
    for (; u >= 0; ) {
        if (i >= _)
            l = t[u] >> i - _ & c;
        else {
            l = (t[u] & (1 << i + 1) - 1) << _ - i;
            if (u > 0)
                l |= t[u - 1] >> this.DB + i - _
        }
        a = n;
        for (; 0 == (1 & l); ) {
            l >>= 1;
            --a
        }
        if ((i -= a) < 0) {
            i += this.DB;
            --u
        }
        if (d) {
            o[l].copyTo(r);
            d = !1
        } else {
            for (; a > 1; ) {
                s.sqrTo(r, f);
                s.sqrTo(f, r);
                a -= 2
            }
            if (a > 0)
                s.sqrTo(r, f);
            else {
                m = r;
                r = f;
                f = m
            }
            s.mulTo(f, o[l], r)
        }
        for (; u >= 0 && 0 == (t[u] & 1 << i); ) {
            s.sqrTo(r, f);
            m = r;
            r = f;
            f = m;
            if (--i < 0) {
                i = this.DB - 1;
                --u
            }
        }
    }
    return s.revert(r)
}
function bnGCD(t) {
    var e = this.s < 0 ? this.negate() : this.clone();
    var i = t.s < 0 ? t.negate() : t.clone();
    if (e.compareTo(i) < 0) {
        var n = e;
        e = i;
        i = n
    }
    var r = e.getLowestSetBit()
      , s = i.getLowestSetBit();
    if (s < 0)
        return e;
    if (r < s)
        s = r;
    if (s > 0) {
        e.rShiftTo(s, e);
        i.rShiftTo(s, i)
    }
    for (; e.signum() > 0; ) {
        if ((r = e.getLowestSetBit()) > 0)
            e.rShiftTo(r, e);
        if ((r = i.getLowestSetBit()) > 0)
            i.rShiftTo(r, i);
        if (e.compareTo(i) >= 0) {
            e.subTo(i, e);
            e.rShiftTo(1, e)
        } else {
            i.subTo(e, i);
            i.rShiftTo(1, i)
        }
    }
    if (s > 0)
        i.lShiftTo(s, i);
    return i
}
function bnpModInt(t) {
    if (t <= 0)
        return 0;
    var e = this.DV % t
      , i = this.s < 0 ? t - 1 : 0;
    if (this.t > 0)
        if (0 == e)
            i = this[0] % t;
        else
            for (var n = this.t - 1; n >= 0; --n)
                i = (e * i + this[n]) % t;
    return i
}
function bnModInverse(t) {
    var e = t.isEven();
    if (this.isEven() && e || 0 == t.signum())
        return BigInteger.ZERO;
    var i = t.clone()
      , n = this.clone();
    var r = nbv(1)
      , s = nbv(0)
      , o = nbv(0)
      , a = nbv(1);
    for (; 0 != i.signum(); ) {
        for (; i.isEven(); ) {
            i.rShiftTo(1, i);
            if (e) {
                if (!r.isEven() || !s.isEven()) {
                    r.addTo(this, r);
                    s.subTo(t, s)
                }
                r.rShiftTo(1, r)
            } else if (!s.isEven())
                s.subTo(t, s);
            s.rShiftTo(1, s)
        }
        for (; n.isEven(); ) {
            n.rShiftTo(1, n);
            if (e) {
                if (!o.isEven() || !a.isEven()) {
                    o.addTo(this, o);
                    a.subTo(t, a)
                }
                o.rShiftTo(1, o)
            } else if (!a.isEven())
                a.subTo(t, a);
            a.rShiftTo(1, a)
        }
        if (i.compareTo(n) >= 0) {
            i.subTo(n, i);
            if (e)
                r.subTo(o, r);
            s.subTo(a, s)
        } else {
            n.subTo(i, n);
            if (e)
                o.subTo(r, o);
            a.subTo(s, a)
        }
    }
    if (0 != n.compareTo(BigInteger.ONE))
        return BigInteger.ZERO;
    if (a.compareTo(t) >= 0)
        return a.subtract(t);
    if (a.signum() < 0)
        a.addTo(t, a);
    else
        return a;
    if (a.signum() < 0)
        return a.add(t);
    else
        return a
}
var lowprimes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997];
var lplim = (1 << 26) / lowprimes[lowprimes.length - 1];
function bnIsProbablePrime(t) {
    var e, i = this.abs();
    if (1 == i.t && i[0] <= lowprimes[lowprimes.length - 1]) {
        for (e = 0; e < lowprimes.length; ++e)
            if (i[0] == lowprimes[e])
                return !0;
        return !1
    }
    if (i.isEven())
        return !1;
    e = 1;
    for (; e < lowprimes.length; ) {
        var n = lowprimes[e]
          , r = e + 1;
        for (; r < lowprimes.length && n < lplim; )
            n *= lowprimes[r++];
        n = i.modInt(n);
        for (; e < r; )
            if (n % lowprimes[e++] == 0)
                return !1
    }
    return i.millerRabin(t)
}
function bnpMillerRabin(t) {
    var e = this.subtract(BigInteger.ONE);
    var i = e.getLowestSetBit();
    if (i <= 0)
        return !1;
    var n = e.shiftRight(i);
    t = t + 1 >> 1;
    if (t > lowprimes.length)
        t = lowprimes.length;
    var r = nbi();
    for (var s = 0; s < t; ++s) {
        r.fromInt(lowprimes[Math.floor(Math.random() * lowprimes.length)]);
        var o = r.modPow(n, this);
        if (0 != o.compareTo(BigInteger.ONE) && 0 != o.compareTo(e)) {
            var a = 1;
            for (; a++ < i && 0 != o.compareTo(e); ) {
                o = o.modPowInt(2, this);
                if (0 == o.compareTo(BigInteger.ONE))
                    return !1
            }
            if (0 != o.compareTo(e))
                return !1
        }
    }
    return !0
}
BigInteger.prototype.chunkSize = bnpChunkSize;
BigInteger.prototype.toRadix = bnpToRadix;
BigInteger.prototype.fromRadix = bnpFromRadix;
BigInteger.prototype.fromNumber = bnpFromNumber;
BigInteger.prototype.bitwiseTo = bnpBitwiseTo;
BigInteger.prototype.changeBit = bnpChangeBit;
BigInteger.prototype.addTo = bnpAddTo;
BigInteger.prototype.dMultiply = bnpDMultiply;
BigInteger.prototype.dAddOffset = bnpDAddOffset;
BigInteger.prototype.multiplyLowerTo = bnpMultiplyLowerTo;
BigInteger.prototype.multiplyUpperTo = bnpMultiplyUpperTo;
BigInteger.prototype.modInt = bnpModInt;
BigInteger.prototype.millerRabin = bnpMillerRabin;
BigInteger.prototype.clone = bnClone;
BigInteger.prototype.intValue = bnIntValue;
BigInteger.prototype.byteValue = bnByteValue;
BigInteger.prototype.shortValue = bnShortValue;
BigInteger.prototype.signum = bnSigNum;
BigInteger.prototype.toByteArray = bnToByteArray;
BigInteger.prototype.equals = bnEquals;
BigInteger.prototype.min = bnMin;
BigInteger.prototype.max = bnMax;
BigInteger.prototype.and = bnAnd;
BigInteger.prototype.or = bnOr;
BigInteger.prototype.xor = bnXor;
BigInteger.prototype.andNot = bnAndNot;
BigInteger.prototype.not = bnNot;
BigInteger.prototype.shiftLeft = bnShiftLeft;
BigInteger.prototype.shiftRight = bnShiftRight;
BigInteger.prototype.getLowestSetBit = bnGetLowestSetBit;
BigInteger.prototype.bitCount = bnBitCount;
BigInteger.prototype.testBit = bnTestBit;
BigInteger.prototype.setBit = bnSetBit;
BigInteger.prototype.clearBit = bnClearBit;
BigInteger.prototype.flipBit = bnFlipBit;
BigInteger.prototype.add = bnAdd;
BigInteger.prototype.subtract = bnSubtract;
BigInteger.prototype.multiply = bnMultiply;
BigInteger.prototype.divide = bnDivide;
BigInteger.prototype.remainder = bnRemainder;
BigInteger.prototype.divideAndRemainder = bnDivideAndRemainder;
BigInteger.prototype.modPow = bnModPow;
BigInteger.prototype.modInverse = bnModInverse;
BigInteger.prototype.pow = bnPow;
BigInteger.prototype.gcd = bnGCD;
BigInteger.prototype.isProbablePrime = bnIsProbablePrime;
BigInteger.prototype.square = bnSquare;
if ("object" != typeof JSON)
    JSON = {};
!function() {
    "use strict";
    function f(t) {
        return t < 10 ? "0" + t : t
    }
    function quote(t) {
        escapable.lastIndex = 0;
        return escapable.test(t) ? '"' + t.replace(escapable, function(t) {
            var e = meta[t];
            return "string" == typeof e ? e : "\\u" + ("0000" + t.charCodeAt(0).toString(16)).slice(-4)
        }) + '"' : '"' + t + '"'
    }
    function str(t, e) {
        var i, n, r, s, o = gap, a, _ = e[t];
        if (_ && "object" == typeof _ && "function" == typeof _.toJSON)
            _ = _.toJSON(t);
        if ("function" == typeof rep)
            _ = rep.call(e, t, _);
        switch (typeof _) {
        case "string":
            return quote(_);
        case "number":
            return isFinite(_) ? String(_) : "null";
        case "boolean":
        case "null":
            return String(_);
        case "object":
            if (!_)
                return "null";
            gap += indent;
            a = [];
            if ("[object Array]" === Object.prototype.toString.apply(_)) {
                s = _.length;
                for (i = 0; i < s; i += 1)
                    a[i] = str(i, _) || "null";
                r = 0 === a.length ? "[]" : gap ? "[\n" + gap + a.join(",\n" + gap) + "\n" + o + "]" : "[" + a.join(",") + "]";
                gap = o;
                return r
            }
            if (rep && "object" == typeof rep) {
                s = rep.length;
                for (i = 0; i < s; i += 1)
                    if ("string" == typeof rep[i]) {
                        n = rep[i];
                        r = str(n, _);
                        if (r)
                            a.push(quote(n) + (gap ? ": " : ":") + r)
                    }
            } else
                for (n in _)
                    if (Object.prototype.hasOwnProperty.call(_, n)) {
                        r = str(n, _);
                        if (r)
                            a.push(quote(n) + (gap ? ": " : ":") + r)
                    }
            r = 0 === a.length ? "{}" : gap ? "{\n" + gap + a.join(",\n" + gap) + "\n" + o + "}" : "{" + a.join(",") + "}";
            gap = o;
            return r
        }
    }
    if ("function" != typeof Date.prototype.toJSON) {
        Date.prototype.toJSON = function() {
            return isFinite(this.valueOf()) ? this.getUTCFullYear() + "-" + f(this.getUTCMonth() + 1) + "-" + f(this.getUTCDate()) + "T" + f(this.getUTCHours()) + ":" + f(this.getUTCMinutes()) + ":" + f(this.getUTCSeconds()) + "Z" : null
        }
        ;
        String.prototype.toJSON = Number.prototype.toJSON = Boolean.prototype.toJSON = function() {
            return this.valueOf()
        }
    }
    var cx, escapable, gap, indent, meta, rep;
    if ("function" != typeof JSON.stringify) {
        escapable = /[\\\"\x00-\x1f\x7f-\x9f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g;
        meta = {
            "\b": "\\b",
            "\t": "\\t",
            "\n": "\\n",
            "\f": "\\f",
            "\r": "\\r",
            '"': '\\"',
            "\\": "\\\\"
        };
        JSON.stringify = function(t, e, i) {
            var n;
            gap = "";
            indent = "";
            if ("number" == typeof i)
                for (n = 0; n < i; n += 1)
                    indent += " ";
            else if ("string" == typeof i)
                indent = i;
            rep = e;
            if (e && "function" != typeof e && ("object" != typeof e || "number" != typeof e.length))
                throw new Error("JSON.stringify");
            return str("", {
                "": t
            })
        }
    }
    if ("function" != typeof JSON.parse) {
        cx = /[\u0000\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g;
        JSON.parse = function(text, reviver) {
            function walk(t, e) {
                var i, n, r = t[e];
                if (r && "object" == typeof r)
                    for (i in r)
                        if (Object.prototype.hasOwnProperty.call(r, i)) {
                            n = walk(r, i);
                            if (void 0 !== n)
                                r[i] = n;
                            else
                                delete r[i]
                        }
                return reviver.call(t, e, r)
            }
            var j;
            text = String(text);
            cx.lastIndex = 0;
            if (cx.test(text))
                text = text.replace(cx, function(t) {
                    return "\\u" + ("0000" + t.charCodeAt(0).toString(16)).slice(-4)
                });
            if (/^[\],:{}\s]*$/.test(text.replace(/\\(?:["\\\/bfnrt]|u[0-9a-fA-F]{4})/g, "@").replace(/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g, "]").replace(/(?:^|:|,)(?:\s*\[)+/g, ""))) {
                j = eval("(" + text + ")");
                return "function" == typeof reviver ? walk({
                    "": j
                }, "") : j
            }
            throw new SyntaxError("JSON.parse")
        }
    }
}();
var Hex = {
    hex: "0123456789abcdef",
    encode: function(t) {
        if (!t)
            return !1;
        var e = "";
        var i;
        var n = 0;
        do {
            i = t.charCodeAt(n++);
            e += this.hex.charAt(i >> 4 & 15) + this.hex.charAt(15 & i)
        } while (n < t.length);return e
    },
    decode: function(t) {
        if (!t)
            return !1;
        t = t.replace(/[^0-9abcdef]/g, "");
        var e = "";
        var i = 0;
        do
            e += String.fromCharCode(this.hex.indexOf(t.charAt(i++)) << 4 & 240 | 15 & this.hex.indexOf(t.charAt(i++)));
        while (i < t.length);return e
    }
};
LeyBc("Hello")
