//
// Created by Nathan on 12/03/2021.
//

#include "HNF.h"

/*

     Utrecht, July 1998


     The usage of this version of notextendedlll is

     notextendedlll(m,quality,reduceoff)

     where
     m is a matrix of integers.
     quality is a rational number, 1/4 < quality < 1.
     (The usual choice is 3/4. If you are in a hurry, try 1/3)
     reduceoff=1 means that we do NOT need a reduced lattice basis,
                       just a basis of the lattice spanned by the columns.
     reduceoff=0 means that we want a reduced lattice basis.

     The output of notextendedlll is the new basis (as columns).
     The transformation matrix is not computed, which may speed things up.

     One can install notextendedlll inside GP with
     a command like

	install("notextendedlll","GGL","notextendedlll",\
	"mypath/libnotextendedlll.so")

     where mypath tells where libnotextendedlll.so is to be found.

     The code still contains curious remnants of the extendedlll code.


     Wilberd van der Kallen
     http://www.math.uu.nl/people/vdkallen/kallen.html

*/
/*
#include "genpari.h"

GEN notextendedlll(GEN,GEN,long);


 produit scalaire de x par y sans verification de compatibilite
static GEN
gscal(GEN x,GEN y)
{
    GEN z,p;
    long i,av,tetpil,lx=lg(x);

    z=gzero; if (lx==1) return z;
    av=avma;
    for (i=1; i<lx; i++)
    {
        p=gmul((GEN)x[i],(GEN)y[i]);
        tetpil=avma; z=gadd(z,p);
    }
    return gerepile(av,tetpil,z);
}





GEN notextendedlll(GEN x, GEN z,  long   reduceoff)
{
    long av=avma,av1,tetpil,lx=lg(x),tx=typ(x),i,j,k,l,p1,n,lim,dec,q2,\
       s1,isodim,kk,kmax,ll,next,notfinished,rnk,s,cond;
    GEN u,B,lam,q,r,h,p2,p3,p4,p5,\
      a,c,d,Matr11,Matr12,Matr21,Matr22,numz,denz,\
      qq,t1,t3,tmp,tmp2,v1,v3,y, *gptr[5];

    if(tx!=19) err(talker," notextendedlll: argument is no matrix");
    l=lg((GEN)x[1]);
    for(i=1;i<l;i++)
        for(j=1;j<lx;j++)
        {if(typ((GEN)coeff(x,i,j))!=1)
                err(talker," notextendedlll: matrix entry is no integer");
        }
    av=avma;lim=(avma+bot)>>1;
    numz=numer(z);
    denz=denom(z);
    if(typ(numz)!=1)
        err(talker," notextendedlll: ratio is not a rational number");
    if(typ(denz)!=1)
        err(talker," notextendedlll: ratio is not a rational number");
    if((cmpii(numz,denz)>=0))
        err(talker," notextendedlll: ratio is not <1");
    if((cmpii(denz,shifti(numz,2))>=0))
        err(talker," notextendedlll: ratio is not >1/4");
    av1=avma;
    B=cgetg(lx+2,18);
    for(j=1;j<=lx+1;j++) B[j]=un;
    lam=cgetg(lx,19);
    for(j=1;j<lx;j++) lam[j]=lgetg(lx,18);
    for(i=1;i<lx;i++)
        for(j=1;j<lx;j++)
        {coeff(lam,i,j)=zero;
        }
    if(1-reduceoff) {s1=1;} else {s1=0;}
    notfinished=1;
    n=lx-1;
    h=idmat(n);
    for(i=1;i<lx;i++) h[i]=lcopy((GEN)x[i]);
    rnk=isodim=0;
    kmax=k=1;
    r=cgetg(lx,18);
    for(i=1;i<lx;i++) r[i]=un;
    B[k+2]=(long)gscal((GEN)h[k],(GEN)h[k]);
    s=signe((GEN)B[k+2]);
    if(s<=0)
    {isodim=isodim+1;
        B[isodim+2]=un;
        B[k+1]=un;
    }
    else
    {rnk++;
    };
    next=0;
    k=2;
    if(k<=n) {next=1;} else {notfinished=0;}
    while(notfinished)
    {
        if (DEBUGLEVEL>5) { fprintferr(" k = %ld",k); flusherr(); };
        if(next)
        {if(k>kmax)
            {kmax=k;
                if (DEBUGLEVEL>3) { fprintferr(" kmax = %ld\n",k); flusherr(); };
                for(j=isodim+1;j<=k;j++)
                {
                    q=gscal((GEN)h[j],(GEN)h[k]);
                    for(i=isodim+1;i<j;i++)
                    {q=divii(subii(mulii(q,(GEN)B[i+2]),
                                   mulii(gcoeff(lam,k,i),gcoeff(lam,j,i))),(GEN)B[1+i]);
                    };
                    if(j<k) {coeff(lam,k,j)=(long)q;} else {B[k+2]=(long)q;}
                    if (low_stack(lim, (av1+bot)>>1))
                    {
                        if(DEBUGMEM>1) err(warnmem,"[1]:  notextendedlll");
                        gptr[0]=&B; gptr[1]=&h; gptr[2]=&r; gptr[3]=&lam;
                        gerepilemany(av1,gptr,4);
                    }
                };
                s=signe((GEN)B[k+2]);
                if(s<=0)
                {
                    if(s) err(talker,
                              " notextendedlll: This should not happen.");
                    for(i=1;i<=kmax;i++) r[i]=un;
                    for(i=1;i<=rnk;i++)
                    {
                        k--;
                        a=(GEN)B[k+2];c=gcoeff(lam,k+1,k);Matr21=gun;d=a;
                        if(signe(c))
                        {
                            v1=gzero;v3=c;
                            while(signe(v3))
                            {
                                qq=gdiventres(d,v3);
                                q=(GEN)qq[1];t3=(GEN)qq[2];
                                t1=subii(Matr21,mulii(q,v1));
                                Matr21=v1;d=v3;v1=t1;v3=t3;
                            };
                            Matr22=divii(subii(d,mulii(a,Matr21)),c);
                        }
                        else
                        {
                            Matr22=gzero;
                        };
                        Matr11=gneg(divii(c,d));
                        Matr12=divii(a,d);
                        r[k+1]=(long)Matr12;
                        tmp=gadd(gmul(Matr11,(GEN)h[k]),gmul(Matr12,(GEN)h[k+1]));
                        h[k+1]=ladd(gmul(Matr21,(GEN)h[k]),gmul(Matr22,(GEN)h[k+1]));
                        h[k]=(long)tmp;
                        for(j=1;j<k;j++)
                        {
                            q=addii(mulii(Matr11,gcoeff(lam,k,j)),
                                    mulii(Matr12,gcoeff(lam,k+1,j)));
                            coeff(lam,k+1,j)=
                                    (long)addii(mulii(Matr21,gcoeff(lam,k,j)),
                                                mulii(Matr22,gcoeff(lam,k+1,j)));
                            coeff(lam,k,j)=(long)q;
                        };
                        if (low_stack(lim, (av1+bot)>>1))
                        {
                            if(DEBUGMEM>1) err(warnmem,"[2]:  notextendedlll");
                            gptr[0]=&B; gptr[1]=&h; gptr[2]=&r; gptr[3]=&lam;
                            gerepilemany(av1,gptr,4);
                        }
                        for(l=(k-1);l>=1;l--)
                        {
                            if (low_stack(lim, (av1+bot)>>1))
                            {
                                if(DEBUGMEM>1) err(warnmem,"[3]:  notextendedlll");
                                gptr[0]=&B; gptr[1]=&h; gptr[2]=&r; gptr[3]=&lam;
                                gerepilemany(av1,gptr,4);
                            }
                            if(l>isodim) {a=(GEN)B[l+2];} else {a=(GEN)B[l+1];}
                            if((cmpii(absi(u=shifti(gcoeff(lam,k,l),1)),a)>0))
                            {q=dvmdii(addii(u,a),shifti(a,1),&y);
                                if(signe(y)<0) q=addsi(-1,q);
                                h[k]=lsub((GEN)h[k],gmul(q,(GEN)h[l]));
                                coeff(lam,k,l)=lsubii(gcoeff(lam,k,l),mulii(q,a));
                                for(j=1;j<l;j++)
                                    coeff(lam,k,j)=
                                            lsubii(gcoeff(lam,k,j),mulii(q,gcoeff(lam,l,j)));
                            }
                        }
                    };
                    isodim=isodim+1;
                    for(i=isodim+1;i<=kmax;i++) {r[i]=lmul((GEN)r[i],(GEN)r[i-1]);}
                    for(k=kmax;k>isodim;k--)
                    {B[k+2]=ldivii((GEN)B[1+k],mulii(u=(GEN)r[k],(GEN)r[k]));
                        q=mulii(u,(GEN)r[k-1]);
                        for(j=k+1;j<=kmax;j++)
                        {coeff(lam,j,k)=ldivii(gcoeff(lam,j,k-1),q);
                        };
                        if (low_stack(lim, (av1+bot)>>1))
                        {
                            if(DEBUGMEM>1) err(warnmem,"[4]:  notextendedlll");
                            gptr[0]=&B; gptr[1]=&h; gptr[2]=&r; gptr[3]=&lam;
                            gerepilemany(av1,gptr,4);
                        }
                    };
                    B[isodim+2]=un;

The column with number isodim of h is now zero. We do not like dependent
columns. So we imagine an extra row to be added with a one in the isodim
entry and zeroes elsewhere. Thus we can pretend the columns to be
independent and we fill the tables accordingly. That way we can run the
algorithm as if there is no dependence. We will throw away the first isodim
columns at the end anyway. As in extendedlll we must avoid swapping the
columns with numbers isodim and isodim+1.

                    for(k=1;k<=isodim;k++)
                    {kk=isodim;ll=k;
                        if(ll<kk)
                        {coeff(lam,kk,ll)=zero;
                        }
                        else
                        {B[kk+1]=un;
                        };
                        if (low_stack(lim, (av1+bot)>>1))
                        {
                            if(DEBUGMEM>1) err(warnmem,"[5]:  notextendedlll");
                            gptr[0]=&B; gptr[1]=&h; gptr[2]=&r; gptr[3]=&lam;
                            gerepilemany(av1,gptr,4);
                        }
                    }
                    for(k=isodim+1;k<=kmax;k++)
                    {kk=k;ll=isodim;
                        if(ll<kk)
                        {coeff(lam,kk,ll)=zero;
                        }
                        else
                        {B[kk+1]=un;
                        };
                    }
                    for(k=isodim;k<=kmax;k++)
                    {
                        for(l=(k-1);l>=1;l--)
                        {
                            if (low_stack(lim, (av1+bot)>>1))
                            {
                                if(DEBUGMEM>1) err(warnmem,"[6]:  notextendedlll");
                                gptr[0]=&B; gptr[1]=&h; gptr[2]=&r; gptr[3]=&lam;
                                gerepilemany(av1,gptr,4);
                            }
                            if(l>isodim) {a=(GEN)B[l+2];} else {a=(GEN)B[l+1];}
                            if((cmpii(absi(u=shifti(gcoeff(lam,k,l),1)),a)>0))
                            {q=dvmdii(addii(u,a),shifti(a,1),&y);
                                if(signe(y)<0) q=addsi(-1,q);
                                h[k]=lsub((GEN)h[k],gmul(q,(GEN)h[l]));
                                coeff(lam,k,l)=lsubii(gcoeff(lam,k,l),mulii(q,a));
                                for(i=1;i<l;i++)
                                    coeff(lam,k,i)=
                                            lsubii(gcoeff(lam,k,i),mulii(q,gcoeff(lam,l,i)));
                            }
                        }
                    }
                    if(isodim>2) {k=isodim;} else {k=2;}
                }
                else
                {rnk++;
                };
            }
            next=0;
        }
        else
        {l=(k-1);
            if(l>isodim) {a=(GEN)B[l+2];} else {a=(GEN)B[l+1];}
            if((cmpii(absi(u=shifti(gcoeff(lam,k,l),1)),a)>0))
            {q=dvmdii(addii(u,a),shifti(a,1),&y);
                if(signe(y)<0) q=addsi(-1,q);
                h[k]=lsub((GEN)h[k],gmul(q,(GEN)h[l]));
                coeff(lam,k,l)=lsubii(gcoeff(lam,k,l),mulii(q,a));
                for(i=1;i<l;i++)
                    coeff(lam,k,i)=
                            lsubii(gcoeff(lam,k,i),mulii(q,gcoeff(lam,l,i)));
            }
            if (low_stack(lim, (av1+bot)>>1))
            {
                if(DEBUGMEM>1) err(warnmem,"[7]:  notextendedlll");
                gptr[0]=&B; gptr[1]=&h; gptr[2]=&r; gptr[3]=&lam;
                gerepilemany(av1,gptr,4);
            }
            if(k>isodim+1)
            {p2=(GEN)B[k+2];p5=(GEN)B[k+1];cond=s1&&(
                        (cmpii(mulii(numz,mulii(p5,p5)),
                               mulii(denz,addii(p3=mulii((GEN)B[k],p2),
                                                p4=mulii(q=(GEN)coeff(lam,k,l),
                                                         gcoeff(lam,k,l)))))>0));
            }
            else
            {cond=(0==1);
            }
            if(cond)
            {p1=h[l];h[l]=h[k];h[k]=p1;
                for(j=1;j<=k-2;j++)
                {
                    p1=coeff(lam,l,j);coeff(lam,l,j)=coeff(lam,k,j);
                    coeff(lam,k,j)=p1;
                }
                u=divii(addii(p3,p4),p5);
                for(i=k+1;i<=kmax;i++)
                {   a=gcoeff(lam,i,k);
                    coeff(lam,i,k)=ldivii(
                            subii(mulii(p2,gcoeff(lam,i,l)),mulii(q,a)),
                            (GEN)p5);
                    coeff(lam,i,l)=ldivii(
                            addii(mulii(q,gcoeff(lam,i,k)),mulii(u,a)),
                            (GEN)p2);
                }
                if(k>isodim) {B[k+1]=(long)u;} else {B[k]=(long)u;}
                if(k>2) k--;
            }
            else
            {
                for(l=k-2;l>0;l--)
                {
                    if (low_stack(lim, (av1+bot)>>1))
                    {
                        if(DEBUGMEM>1) err(warnmem,"[8]:  notextendedlll");
                        gptr[0]=&B; gptr[1]=&h; gptr[2]=&r; gptr[3]=&lam;
                        gerepilemany(av1,gptr,4);
                    }
                    if(l>isodim) {a=(GEN)B[l+2];} else {a=(GEN)B[l+1];}
                    if((cmpii(absi(u=shifti(gcoeff(lam,k,l),1)),a)>0))
                    {q=dvmdii(addii(u,a),shifti(a,1),&y);
                        if(signe(y)<0) q=addsi(-1,q);
                        h[k]=lsub((GEN)h[k],gmul(q,(GEN)h[l]));
                        coeff(lam,k,l)=lsubii(gcoeff(lam,k,l),mulii(q,a));
                        for(i=1;i<l;i++)
                            coeff(lam,k,i)=
                                    lsubii(gcoeff(lam,k,i),mulii(q,gcoeff(lam,l,i)));
                    }
                };
                k++;
                if(k<lx) {next=1;} else {notfinished=0;}
            }
        }
        if (low_stack(lim, (av1+bot)>>1))
        {
            if(DEBUGMEM>1) err(warnmem,"[9]:  notextendedlll");
            gptr[0]=&B; gptr[1]=&h; gptr[2]=&r; gptr[3]=&lam;
            gerepilemany(av1,gptr,4);
        }
    }
    tetpil=avma;
    q=cgetg(lx=rnk+1,19);for(i=1;i<lx;i++) q[i]=lcopy((GEN)h[isodim+i]);
    return gerepile(av,tetpil,q);
}
*/