#ifndef FCGLOBALS_H
#define FCGLOBALS_H
#include <QScopedPointer>
///
/// \def 前置声明的定义
///
#ifndef FC_IMPL_FORWARD_DECL
#define FC_IMPL_FORWARD_DECL(ClassName)	\
    class ClassName ## Private;
#endif
///
/// \def impl的简易实现
///
#ifndef FC_IMPL
#define FC_IMPL(Class)								 \
private:									 \
    inline Class ## Private *d_func() { return (d_ptr.data()); }		 \
    inline const Class ## Private *d_func() const { return (d_ptr.data()); } \
    friend class Class ## Private;						 \
    QScopedPointer<Class ## Private> d_ptr;
#endif
///
/// \def impl的定义
///
#ifndef FC_IMPL_PUBLIC
#define FC_IMPL_PUBLIC(Class)								   \
    inline Class *q_func() { return (static_cast<Class *>(q_ptr)); }		   \
    inline const Class *q_func() const { return (static_cast<const Class *>(q_ptr)); } \
    friend class Class;								   \
    Class *q_ptr;
#endif
///
/// \def impl获取指针，参考Q_D
///
#ifndef FC_D
#define FC_D(Class) \
    Class ## Private *d = d_func()
#endif
///
/// \def impl获取指针，参考Q_D
///
#ifndef FC_DC
#define FC_DC(Class) \
    const Class ## Private *d = d_func()
#endif
///
/// \def impl获取指针，参考Q_Q
///
#ifndef FC_Q
#define FC_Q(Class) \
    Class *q = q_func()
#endif
///
/// \def impl获取指针，参考Q_Q
///
#ifndef FC_QC
#define FC_QC(Class) \
    const Class *q = q_func()
#endif




#endif // GLOBALS_H
