#ifndef DAOZHAI_C_H
#define DAOZHAI_C_H

class daozhai_abs_c
{
public:
    daozhai_abs_c();

    int jiaodu(void);


    virtual bool sig_kai(void)=0;
    virtual bool sig_guan(void)=0;
    virtual bool sig_ting(void)=0;
    void * run(void *parg);
protected:
    virtual void set_kai_xw(bool status)=0;
    virtual void set_guan_xw(bool status)=0;


private:
    int err;
    int m_jiaodu;
    int tim;
};


//
class daozhai_c:public daozhai_abs_c
{
public:
    daozhai_c();
    static daozhai_c *get_intance(void);


    virtual bool sig_kai(void);
    virtual bool sig_guan(void);
    virtual bool sig_ting(void);
protected:
    virtual void set_kai_xw(bool status);
    virtual void set_guan_xw(bool status);
};


#endif // DAOZHAI_C_H
