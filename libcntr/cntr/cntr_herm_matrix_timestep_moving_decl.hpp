#ifndef CNTR_HERM_MATRIX_TIMESTEP_MOVING_DECL_H
#define CNTR_HERM_MATRIX_TIMESTEP_MOVING_DECL_H

#include "cntr_herm_matrix_timestep_decl.hpp"
//#include "cntr_exception.hpp"
#include "cntr_elements.hpp"
#include "cntr_function_decl.hpp"
#include "cntr_herm_matrix_decl.hpp"
#include "cntr_herm_matrix_timestep_view_impl.hpp"

namespace cntr {

    /** \brief <b> Class `herm_matrix_timestep_moving` deals with contour objects \f$ C(t,t') \f$
   * at a particular timestep \f$t'\f$.</b>
   *
   * <!-- ====== DOCUMENTATION ====== -->
   *
   *  \par Purpose
   * <!-- ========= -->
   *
   * The class 'herm_matrix_timestep_moving' has almost the same functionality
   * as the class 'herm_matrix_moving'. Here, one considers however contour objects \f$ C(t,t') \f$
   * at a particular timestep \f$t'\f$ (timeslice with respect to the first argument \f$t\f$)
   * The contour function \f$ C(t,t') \f$ can be of scalar type or matrix-valued.
   * NOTE: the bose/fermi sign for the herm_matrix_timestep
   * is currently not consistently treated ... safe only for fermionic Green's functions
   *
   */

  template <typename T> class herm_matrix_timestep_moving{
  public:
    typedef std::complex<T> cplx;
    typedef T scalar_type;
    /* construction, destruction */
    herm_matrix_timestep_moving();
    ~herm_matrix_timestep_moving();
    herm_matrix_timestep_moving(int tc, int t0,int size1=1,int sig=-1);
    herm_matrix_timestep_moving(const herm_matrix_timestep_moving &g);
    herm_matrix_timestep_moving & operator=(const herm_matrix_timestep_moving &g);
    herm_matrix_timestep_moving(int n,herm_matrix_moving<T> &g);
    void clear(void);
    void resize(int tc,int size1);
    /* access size etc ... */
    int element_size(void) const{ return element_size_;}
    int size1(void) const{ return size1_;}
    int size2(void) const{ return size2_;}
    int tc(void) const{ return tc_;}
    int t0(void) const{ return t0_;}
    int sig(void) const{ return sig_;}
    void set_sig(int s);
    void set_t0(int tstp) {t0_=tstp;}
    // raw pointer to elements ... to be used with care
    inline cplx * lesptr(int j){return les_+j*element_size_;}  // points to Gret(t0-i,t0-i-j)
    inline cplx * retptr(int j){return ret_+j*element_size_;}  // points to Gles(t0-i,t0-i-j)
    // reading basic and derived elements to any Matrix type:
    // the get_... address time-arguments "relative to t0"  (i,j) == (t0-i,t0-i-j)
    // and work only for 0 <= i,j <= tc
    /// @private
    template<class Matrix> void get_les(int j,Matrix &M);
    /// @private
    template<class Matrix> void get_gtr(int j,Matrix &M);
    /// @private
    template<class Matrix> void get_ret(int j,Matrix &M);
    // these will adress only (0,0) element for dim>1:
    /// @private
    inline void get_les(int j,cplx &x);
    /// @private
    inline void get_gtr(int j,cplx &x);
    /// @private
    inline void get_ret(int j,cplx &x);
    cplx density_matrix(void);  //  -sig*ii*Gles(t0-i,t0-i)
    template<class Matrix> void density_matrix(Matrix &M);
    // writing basic elements (also relative to t0)
    /// @private
    template<class Matrix> void set_les(int j,Matrix &M);
    /// @private
    template<class Matrix> void set_ret(int j,Matrix &M);
    /// @private
    inline void set_les(int j,cplx x);
    /// @private
    inline void set_ret(int j,cplx x);
    // ADD, CP, SET, MULTIPLY, ETC
    void incr_timestep(herm_matrix_timestep_moving<T> &g,cplx alpha);
    // works only for timestep 0
    void left_multiply(function_moving<T> &g,T weight);
    void right_multiply(function_moving<T> &g,T weight);
    void smul(T weight);
    void smul(cplx weight);
    void incr(function_moving<T> &g, T weight);
    void incr(herm_matrix_timestep_moving<T> &g, T weight);
    // MPI UTILS
#if CNTR_USE_MPI == 1
    void MPI_Reduce(int root);
    //void Bcast_timestep(int tstp, int ntau, int size1, int root);
    //void Send_timestep(int tstp, int ntau, int size1, int dest, int tag);
    //void Recv_timestep(int tstp, int ntau, int size1, int root, int tag);
#endif
  private:
    /** \brief <b> Pointer to the data for the time step (t0). </b> */
    cplx* data_;
    /** \brief <b> Pointer to the lesser part for the time step (t0). 'data_+\f$(tc+1+tc)\f$ * element_size' correponds to (0,0)-component of \f$ G^<(t0,t0-tc)\f$ and 'les_(tc)'. </b> */
    cplx* les_;
    /** \brief <b> Pointer to the retarded part for the time step (t0). 'data_+\f$tc\f$ * element_size' correponds to (0,0)-component of \f$ G^<(t0,t0-tc)\f$ and 'ret_(tc)'. </b> */
    cplx* ret_;
    /** \brief <b> Given cutoff time tc </b> */
    int tc_;
    /** \brief <b> Current physical time step </b> */
    int t0_;
    /** \brief <b> Number of the colums in the Matrix form.</b> */
    int size1_;
    /** \brief <b> Number of the rows in the Matrix form.</b> */
    int size2_;
    /** \brief <b> Size of the Matrix form; size1*size2. </b> */
    int element_size_;
    /** \brief <b> Bose = +1, Fermi =-1. </b> */
    int sig_;
  };

} // namespace cntr

#endif  // CNTR_HERM_MATRIX_TIMESTEP_DECL_H
