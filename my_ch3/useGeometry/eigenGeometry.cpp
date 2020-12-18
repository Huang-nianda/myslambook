#include <iostream>
#include <cmath>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

// 本程序演示了 Eigen 几何模块的使用方法

int main(int argc, char **argv) {

  // Eigen/Geometry 模块提供了各种旋转和平移的表示
  // 3D 旋转矩阵直接使用 Matrix3d 或 Matrix3f
  Matrix3d rotation_matrix = Matrix3d::Identity();
  // 旋转向量使用 AngleAxis, 它底层不直接是Matrix，但运算可以当作矩阵（因为重载了运算符）
  AngleAxisd rotation_vector(M_PI / 4, Vector3d(0,0,1));
  
  
  cout.precision(3); //输出小数点位数
  cout << "rotation matrix =\n" << rotation_vector.matrix() << endl;

  rotation_matrix=rotation_vector.toRotationMatrix();
  cout << "rotation matrix real=\n" << rotation_matrix << endl;
  
  Vector3d v(1,0,0);
  Vector3d v_rotated = rotation_vector * v;
  cout << "(1,0,0) after rotation (by angle axis ) = " <<v_rotated.transpose() <<endl;
  
  v_rotated = rotation_matrix * v;
  cout << "(1,0,0) after rotation (by matrix ) = " <<v_rotated.transpose() <<endl;
  
  Vector3d euler_angles = rotation_matrix.eulerAngles(2,1,0);
  cout << "yaw pitch roll = " << euler_angles.transpose() <<endl;
  
  Isometry3d T = Isometry3d::Identity();
  T.rotate(rotation_vector);
  T.pretranslate(Vector3d(1,3,4));
  cout << "Transform matrix = \n" <<T.matrix() <<endl;
  
  Vector3d v_transformed = T*v;
  cout << "v transformed = " <<v_transformed.transpose() <<endl;
  
  Quaterniond q = Quaterniond(rotation_vector);
  cout << "quaternion from rotation vector =" << q.coeffs().transpose()<<endl;
  
  q = Quaterniond(rotation_matrix);
  cout << "quaternion from rotation matrix =" << q.coeffs().transpose()<<endl;
  
  v_rotated = q * v;
  cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl; 
  
  cout << "should be equal to " << (q* Quaterniond(0,1,0,0) * q.inverse()).coeffs().transpose() << endl;
  
  
  return 0;
}
