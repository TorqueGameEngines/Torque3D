#include "testing/unitTesting.h"

#include "platform/platform.h"
#include "console/simBase.h"
#include "console/consoleTypes.h"
#include "console/scriptObjects.h"
#include "console/simBase.h"
#include "console/engineAPI.h"
#include "math/mMath.h"
#include "math/util/frustum.h"
#include "math/mathUtils.h"

TEST(MatrixTest, TestIdentityInit)
{
   MatrixF test(true);

   EXPECT_NEAR(test(0, 0), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 1), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 2), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestIdentitySet)
{
   MatrixF test(false);
   test.identity();

   EXPECT_NEAR(test(0, 0), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 1), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 2), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestIsIdentity)
{
   MatrixF test(true);
   EXPECT_TRUE(test.isIdentity());
}

TEST(MatrixTest, TestEulerInit)
{
   MatrixF test(EulerF(1.0f, 0.0f, 1.0f));

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);   EXPECT_NEAR(test(0, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.4546f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 0.8415f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.7081f, POINT_EPSILON);   EXPECT_NEAR(test(2, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON); EXPECT_NEAR(test(2, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);      EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}


TEST(MatrixTest, TestEulerSet)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f));

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);   EXPECT_NEAR(test(0, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.4546f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 0.8415f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.7081f, POINT_EPSILON);   EXPECT_NEAR(test(2, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON); EXPECT_NEAR(test(2, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);      EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestToEuler)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f));

   EulerF euler = test.toEuler();

   EXPECT_NEAR(euler.x, 1.0f, POINT_EPSILON); EXPECT_NEAR(euler.y, 0.0f, POINT_EPSILON); EXPECT_NEAR(euler.z, 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestEulerPointInit)
{
   MatrixF test(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);   EXPECT_NEAR(test(0, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 5.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.4546f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 0.8415f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.7081f, POINT_EPSILON);   EXPECT_NEAR(test(2, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON); EXPECT_NEAR(test(2, 3), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);      EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}


TEST(MatrixTest, TestEulerPointSet)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);   EXPECT_NEAR(test(0, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 5.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.4546f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 0.8415f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.7081f, POINT_EPSILON);   EXPECT_NEAR(test(2, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON); EXPECT_NEAR(test(2, 3), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);      EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestGetColumn4)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point4F column;

   test.getColumn(0, &column);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 0), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 0), POINT_EPSILON);

   test.getColumn(1, &column);

   EXPECT_NEAR(column.x, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 1), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 1), POINT_EPSILON);

   test.getColumn(2, &column);

   EXPECT_NEAR(column.x, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 2), POINT_EPSILON);

   test.getColumn(3, &column);

   EXPECT_NEAR(column.x, test(0, 3), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 3), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 3), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 3), POINT_EPSILON);

}

TEST(MatrixTest, TestGetRow4)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point4F column;

   test.getRow(0, &column);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(0, 3), POINT_EPSILON);

   test.getRow(1, &column);

   EXPECT_NEAR(column.x, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(1, 3), POINT_EPSILON);

   test.getRow(2, &column);

   EXPECT_NEAR(column.x, test(2, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(2, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(2, 3), POINT_EPSILON);

   test.getRow(3, &column);

   EXPECT_NEAR(column.x, test(3, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(3, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(3, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 3), POINT_EPSILON);
}

TEST(MatrixTest, TestGetColumn3)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point3F column;

   test.getColumn(0, &column);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 0), POINT_EPSILON);

   test.getColumn(1, &column);

   EXPECT_NEAR(column.x, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 1), POINT_EPSILON);

   test.getColumn(2, &column);

   EXPECT_NEAR(column.x, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);

   test.getColumn(3, &column);

   EXPECT_NEAR(column.x, test(0, 3), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 3), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 3), POINT_EPSILON);

}

TEST(MatrixTest, TestGetRow3)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point3F column;

   test.getRow(0, &column);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(0, 2), POINT_EPSILON);

   test.getRow(1, &column);

   EXPECT_NEAR(column.x, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(1, 2), POINT_EPSILON);

   test.getRow(2, &column);

   EXPECT_NEAR(column.x, test(2, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(2, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);

   test.getRow(3, &column);

   EXPECT_NEAR(column.x, test(3, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(3, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(3, 2), POINT_EPSILON);
}

TEST(MatrixTest, TestGetColumn4F)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point4F column;

   column = test.getColumn4F(0);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 0), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 0), POINT_EPSILON);

   column = test.getColumn4F(1);

   EXPECT_NEAR(column.x, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 1), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 1), POINT_EPSILON);

   column = test.getColumn4F(2);

   EXPECT_NEAR(column.x, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 2), POINT_EPSILON);

   column = test.getColumn4F(3);

   EXPECT_NEAR(column.x, test(0, 3), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 3), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 3), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 3), POINT_EPSILON);

}

TEST(MatrixTest, TestGetRow4F)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point4F column;

   column = test.getRow4F(0);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(0, 3), POINT_EPSILON);

   column = test.getRow4F(1);

   EXPECT_NEAR(column.x, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(1, 3), POINT_EPSILON);

   column = test.getRow4F(2);

   EXPECT_NEAR(column.x, test(2, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(2, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(2, 3), POINT_EPSILON);

   column = test.getRow4F(3);

   EXPECT_NEAR(column.x, test(3, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(3, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(3, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 3), POINT_EPSILON);
}

TEST(MatrixTest, TestGetColumn3F)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point3F column;

   column = test.getColumn3F(0);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 0), POINT_EPSILON);

   column = test.getColumn3F(1);

   EXPECT_NEAR(column.x, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 1), POINT_EPSILON);

   column = test.getColumn3F(2);

   EXPECT_NEAR(column.x, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);

   column = test.getColumn3F(3);

   EXPECT_NEAR(column.x, test(0, 3), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 3), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 3), POINT_EPSILON);

}

TEST(MatrixTest, TestGetRow3F)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point3F column;

   column = test.getRow3F(0);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(0, 2), POINT_EPSILON);

   column = test.getRow3F(1);

   EXPECT_NEAR(column.x, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(1, 2), POINT_EPSILON);

   column = test.getRow3F(2);

   EXPECT_NEAR(column.x, test(2, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(2, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);

   column = test.getRow3F(3);

   EXPECT_NEAR(column.x, test(3, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(3, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(3, 2), POINT_EPSILON);
}

TEST(MatrixTest, TestSetColumn4)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point4F column(1.0f, 1.0f, 1.0f, 1.0f);

   test.setColumn(0, column);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 0), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 0), POINT_EPSILON);

   test.setColumn(1, column);

   EXPECT_NEAR(column.x, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 1), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 1), POINT_EPSILON);

   test.setColumn(2, column);

   EXPECT_NEAR(column.x, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 2), POINT_EPSILON);

   test.setColumn(3, column);

   EXPECT_NEAR(column.x, test(0, 3), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 3), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 3), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 3), POINT_EPSILON);
}

TEST(MatrixTest, TestSetRow4)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point4F column(1.0f, 1.0f, 1.0f, 1.0f);

   test.setRow(0, column);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(0, 3), POINT_EPSILON);

   test.setRow(1, column);

   EXPECT_NEAR(column.x, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(1, 3), POINT_EPSILON);

   test.setRow(2, column);

   EXPECT_NEAR(column.x, test(2, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(2, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(2, 3), POINT_EPSILON);

   test.setRow(3, column);

   EXPECT_NEAR(column.x, test(3, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(3, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(3, 2), POINT_EPSILON);
   EXPECT_NEAR(column.w, test(3, 3), POINT_EPSILON);
}

TEST(MatrixTest, TestSetColumn3)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point3F column(1.0f, 1.0f, 1.0f);

   test.setColumn(0, column);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 0), POINT_EPSILON);

   test.setColumn(1, column);

   EXPECT_NEAR(column.x, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 1), POINT_EPSILON);

   test.setColumn(2, column);

   EXPECT_NEAR(column.x, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);

   test.setColumn(3, column);

   EXPECT_NEAR(column.x, test(0, 3), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 3), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 3), POINT_EPSILON);
}

TEST(MatrixTest, TestSetRow3)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point3F column(1.0f, 1.0f, 1.0f);

   test.setRow(0, column);

   EXPECT_NEAR(column.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(0, 2), POINT_EPSILON);

   test.setRow(1, column);

   EXPECT_NEAR(column.x, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(1, 2), POINT_EPSILON);

   test.setRow(2, column);

   EXPECT_NEAR(column.x, test(2, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(2, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(2, 2), POINT_EPSILON);

   test.setRow(3, column);

   EXPECT_NEAR(column.x, test(3, 0), POINT_EPSILON);
   EXPECT_NEAR(column.y, test(3, 1), POINT_EPSILON);
   EXPECT_NEAR(column.z, test(3, 2), POINT_EPSILON);
}

TEST(MatrixTest, TestDisplace)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   Point3F column(1.0f, 1.0f, 1.0f);

   test.displace(column);

   EXPECT_NEAR(test(0, 3), 6.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 3), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 3), 2.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestGetVectorFunctions)
{
   MatrixF test(true);

   test.set(EulerF(1.0f, 0.0f, 1.0f), Point3F(5.0f, 0.0f, 1.0f));

   VectorF vector;

   vector = test.getRightVector();

   EXPECT_NEAR(vector.x, test(0, 0), POINT_EPSILON);
   EXPECT_NEAR(vector.y, test(1, 0), POINT_EPSILON);
   EXPECT_NEAR(vector.z, test(2, 0), POINT_EPSILON);

   vector = test.getForwardVector();

   EXPECT_NEAR(vector.x, test(0, 1), POINT_EPSILON);
   EXPECT_NEAR(vector.y, test(1, 1), POINT_EPSILON);
   EXPECT_NEAR(vector.z, test(2, 1), POINT_EPSILON);

   vector = test.getUpVector();

   EXPECT_NEAR(vector.x, test(0, 2), POINT_EPSILON);
   EXPECT_NEAR(vector.y, test(1, 2), POINT_EPSILON);
   EXPECT_NEAR(vector.z, test(2, 2), POINT_EPSILON);
}

TEST(MatrixTest, TestSetCrossProduct)
{
   MatrixF test(true);

   test.setCrossProduct(Point3F(5.0f, 0.0f, 1.0f));

   EXPECT_NEAR(test(0, 0), 0.0f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), -1.0f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);  EXPECT_NEAR(test(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 1.0f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.0, POINT_EPSILON);    EXPECT_NEAR(test(1, 2), -5.0f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0f, POINT_EPSILON);  EXPECT_NEAR(test(2, 1), 5.0f, POINT_EPSILON);   EXPECT_NEAR(test(2, 2), 0.0f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);  EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);   EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);  EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestSetTensorProduct)
{
   MatrixF test(true);

   test.setTensorProduct(Point3F(5.0f, 2.0f, 1.0f), Point3F(5.0f, 2.0f, 1.0f));

   EXPECT_NEAR(test(0, 0), 25.0f, POINT_EPSILON); EXPECT_NEAR(test(0, 1), 10.0f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 5.0f, POINT_EPSILON);  EXPECT_NEAR(test(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 10.0f, POINT_EPSILON); EXPECT_NEAR(test(1, 1), 4.0, POINT_EPSILON);    EXPECT_NEAR(test(1, 2), 2.0f, POINT_EPSILON);  EXPECT_NEAR(test(1, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 5.0f, POINT_EPSILON);  EXPECT_NEAR(test(2, 1), 2.0f, POINT_EPSILON);   EXPECT_NEAR(test(2, 2), 1.0f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);  EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);   EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);  EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulFunction)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mul(test2);

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(0, 3), 5.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(1, 3), 2.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test(2, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulOperator)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test = test * test2;

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(0, 3), 5.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(1, 3), 2.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test(2, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), 1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulLFunction)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(0, 3), 4.3845f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(1, 3), -0.8479f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test(2, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), 3.1714, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulArgMatrixFunction)
{
   MatrixF testResult(true);

   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   testResult.mul(test2, test);

   EXPECT_NEAR(testResult(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(testResult(0, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(testResult(0, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(testResult(0, 3), 4.3845f, POINT_EPSILON);
   EXPECT_NEAR(testResult(1, 0), -0.4546f, POINT_EPSILON); EXPECT_NEAR(testResult(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(testResult(1, 2), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(testResult(1, 3), -0.8479f, POINT_EPSILON);
   EXPECT_NEAR(testResult(2, 0), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(testResult(2, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(testResult(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(testResult(2, 3), 3.1714, POINT_EPSILON);
   EXPECT_NEAR(testResult(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(testResult(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(testResult(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(testResult(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulArgMultipleRotationMatrix)
{
   MatrixF testResult(true);

   MatrixF xRot(EulerF(-1.54f, 0.0f, 0.0f));
   MatrixF zRot(EulerF(0.0f, 0.0f, -1.57f));

   testResult.mul(zRot, xRot);

   EXPECT_NEAR(testResult(0, 0), 0.0008f, POINT_EPSILON); EXPECT_NEAR(testResult(0, 1), -0.0308f, POINT_EPSILON);EXPECT_NEAR(testResult(0, 2), 0.9995f, POINT_EPSILON);  EXPECT_NEAR(testResult(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(testResult(1, 0), 1.0f, POINT_EPSILON);    EXPECT_NEAR(testResult(1, 1), 0.0f, POINT_EPSILON);    EXPECT_NEAR(testResult(1, 2), -0.0008f, POINT_EPSILON); EXPECT_NEAR(testResult(1, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(testResult(2, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(testResult(2, 1), 0.9995f, POINT_EPSILON); EXPECT_NEAR(testResult(2, 2), 0.0308f, POINT_EPSILON);  EXPECT_NEAR(testResult(2, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(testResult(3, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(testResult(3, 1), 0.0f, POINT_EPSILON);    EXPECT_NEAR(testResult(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(testResult(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulScalarFunction)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   test.mul(2.0f);

   EXPECT_NEAR(test(0, 0), 1.0806f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), 1.6829f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 8.7689f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.9093f, POINT_EPSILON); EXPECT_NEAR(test(1, 1), 0.5839f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 1.6829f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), -1.6958f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 1.4161f, POINT_EPSILON);  EXPECT_NEAR(test(2, 1), -0.9093f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 1.0806f, POINT_EPSILON); EXPECT_NEAR(test(2, 3), 6.3427f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 2.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulMatScalarFunction)
{
   MatrixF testTran(true);
   testTran.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   testTran.mulL(test2);

   MatrixF test(true);
   test.mul(testTran, 2.0f);

   EXPECT_NEAR(test(0, 0), 1.0806f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), 1.6829f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 8.7689f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.9093f, POINT_EPSILON); EXPECT_NEAR(test(1, 1), 0.5839f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 1.6829f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), -1.6958f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 1.4161f, POINT_EPSILON);  EXPECT_NEAR(test(2, 1), -0.9093f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 1.0806f, POINT_EPSILON); EXPECT_NEAR(test(2, 3), 6.3427f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 2.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulPoint4)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   Point4F testPoint(0.5f, 1.0f, 2.0f, 1.0f);
   test.mul(testPoint);

   EXPECT_NEAR(testPoint.x, 5.4960f, POINT_EPSILON);  EXPECT_NEAR(testPoint.y, 0.8996f, POINT_EPSILON);  EXPECT_NEAR(testPoint.z, 4.1513f, POINT_EPSILON); EXPECT_NEAR(testPoint.w, 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulPoint3)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   Point3F testPoint(0.5f, 1.0f, 2.0f);
   test.mulP(testPoint);

   EXPECT_NEAR(testPoint.x, 5.4960f, POINT_EPSILON);  EXPECT_NEAR(testPoint.y, 0.8996f, POINT_EPSILON);  EXPECT_NEAR(testPoint.z, 4.1513f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulPoint3ToPoint3)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   Point3F point(0.5f, 1.0f, 2.0f);
   Point3F testPoint;
   test.mulP(point, &testPoint);

   EXPECT_NEAR(testPoint.x, 5.4960f, POINT_EPSILON);  EXPECT_NEAR(testPoint.y, 0.8996f, POINT_EPSILON);  EXPECT_NEAR(testPoint.z, 4.1513f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulVector)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   VectorF testPoint(0.5f, 1.0f, 2.0f);
   test.mulV(testPoint);

   EXPECT_NEAR(testPoint.x, 1.1116f, POINT_EPSILON);  EXPECT_NEAR(testPoint.y, 1.7475f, POINT_EPSILON);  EXPECT_NEAR(testPoint.z, 0.9799f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulVectorToPoint3)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   VectorF vec(0.5f, 1.0f, 2.0f);
   Point3F testPoint;
   test.mulV(vec, &testPoint);

   EXPECT_NEAR(testPoint.x, 1.1116f, POINT_EPSILON);  EXPECT_NEAR(testPoint.y, 1.7475f, POINT_EPSILON);  EXPECT_NEAR(testPoint.z, 0.9799f, POINT_EPSILON);
}

TEST(MatrixTest, TestMulBox)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   Box3F testBox(1.0f);

   test.mul(testBox);

   EXPECT_NEAR(testBox.minExtents.x, 4.5f, POINT_EPSILON); EXPECT_NEAR(testBox.minExtents.y, 1.5f, POINT_EPSILON); EXPECT_NEAR(testBox.minExtents.z, 0.5f, POINT_EPSILON);
   EXPECT_NEAR(testBox.maxExtents.x, 5.5f, POINT_EPSILON); EXPECT_NEAR(testBox.maxExtents.y, 2.5f, POINT_EPSILON); EXPECT_NEAR(testBox.maxExtents.z, 1.5f, POINT_EPSILON);
}

TEST(MatrixTest, TestMatrixAdd)
{
   MatrixF test(true);
   MatrixF test2(true);
   for (U32 i = 0; i < 4; i++)
   {
      for (U32 j = 0; j < 4; j++)
      {
         test(i, j) = 1.0f;
         test2(i, j) = 1.0f;
      }
   }

   test.add(test2);

   for (U32 i = 0; i < 4; i++)
   {
      for (U32 j = 0; j < 4; j++)
      {
         EXPECT_NEAR(test(i,j), 2.0f, POINT_EPSILON);
      }
   }

}

TEST(MatrixTest, TestFrustumProjectionMatrix)
{
   MatrixF test(true);
   Frustum testFrustum(false, -0.119894862f, 0.119894862f, 0.0767327100f, -0.0767327100f, 0.1f, 1000.0f);

   testFrustum.getProjectionMatrix(&test);

   EXPECT_NEAR(test(0, 0), 0.8341f, POINT_EPSILON); EXPECT_NEAR(test(0, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(1, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(1, 2), 1.3032f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.0, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(2, 1), -0.0001f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(2, 3), 0.1f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 1), 1.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 0.0f, POINT_EPSILON);

   test.reverseProjection();

   EXPECT_NEAR(test(0, 0), 0.8341f, POINT_EPSILON); EXPECT_NEAR(test(0, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(1, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(1, 2), 1.3032f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.0, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(2, 1), 1.0001f, POINT_EPSILON);  EXPECT_NEAR(test(2, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(2, 3), -0.1f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 1), 1.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 0.0f, POINT_EPSILON);

   test.inverse();

   EXPECT_NEAR(test(0, 0), 1.1989f, POINT_EPSILON); EXPECT_NEAR(test(0, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(1, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(1, 2), 0.9999f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.1f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(2, 1), 0.7673f, POINT_EPSILON);  EXPECT_NEAR(test(2, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(2, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 1), 1.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 0.0f, POINT_EPSILON);

}

TEST(MatrixTest, TestUnProjectStack)
{
   MatrixF saveModel(true);
   MatrixF saveProjection(true);
   RectI renderRect(0 ,0, 1600, 1024);

   Frustum testFrustum(false, -0.119894862f, 0.119894862f, 0.0767327100f, -0.0767327100f, 0.1f, 1000.0f);

   testFrustum.getProjectionMatrix(&saveProjection);

   Point3F dest;
   MathUtils::mProjectScreenToWorld(Point3F(626.0f, 600.0f, 1.0f), &dest, renderRect, saveModel, saveProjection, 0.1f, 10.0f);
   EXPECT_NEAR(dest.x, -0.2868f, POINT_EPSILON);  EXPECT_NEAR(dest.y, 1.1998f, POINT_EPSILON);   EXPECT_NEAR(dest.z, -0.1450f, POINT_EPSILON);
}

TEST(MatrixTest, TestInverse)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   test.inverse();

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(0, 2), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test(0, 3), -5.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), -2.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0, POINT_EPSILON);      EXPECT_NEAR(test(2, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), -1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestInvertTo)
{
   MatrixF test1(true);
   test1.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test1.mulL(test2);

   MatrixF test(true);

   test1.invertTo(&test);

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(0, 2), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test(0, 3), -5.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), -2.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0, POINT_EPSILON);      EXPECT_NEAR(test(2, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), -1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);

   // make sure our original matrix is unchanged
   EXPECT_NEAR(test1(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test1(0, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test1(0, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test1(0, 3), 4.3845f, POINT_EPSILON);
   EXPECT_NEAR(test1(1, 0), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test1(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test1(1, 2), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test1(1, 3), -0.8479f, POINT_EPSILON);
   EXPECT_NEAR(test1(2, 0), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test1(2, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test1(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test1(2, 3), 3.1714, POINT_EPSILON);
   EXPECT_NEAR(test1(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test1(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test1(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test1(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestFullInverse)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   EXPECT_TRUE(test.fullInverse());

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(0, 2), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test(0, 3), -5.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), -2.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0, POINT_EPSILON);      EXPECT_NEAR(test(2, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), -1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestIsAffine)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   EXPECT_TRUE(test.isAffine());
}

TEST(MatrixTest, TestScale)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   test.scale(2.0f);

   EXPECT_NEAR(test(0, 0), 1.0806f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), 1.6829f, POINT_EPSILON);  EXPECT_NEAR(test(0, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(0, 3), 4.3845f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), -0.9093f, POINT_EPSILON); EXPECT_NEAR(test(1, 1), 0.5839f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), 1.6829f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), -0.8479f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 1.4161f, POINT_EPSILON);  EXPECT_NEAR(test(2, 1), -0.9093f, POINT_EPSILON); EXPECT_NEAR(test(2, 2), 1.0806f, POINT_EPSILON); EXPECT_NEAR(test(2, 3), 3.1714f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);    EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestGetScale)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   test.scale(2.0f);

   Point3F scale;
   scale = test.getScale();

   EXPECT_NEAR(scale.x, 2.0f, POINT_EPSILON);  EXPECT_NEAR(scale.y, 2.0f, POINT_EPSILON);  EXPECT_NEAR(scale.z, 2.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestAffineInverse)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   test.affineInverse();

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(0, 2), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test(0, 3), -5.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), -2.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0, POINT_EPSILON);      EXPECT_NEAR(test(2, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), -1.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 1), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 2), 0.0f, POINT_EPSILON);     EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestTranspose)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   test.transpose();

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(0, 2), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0, POINT_EPSILON);      EXPECT_NEAR(test(2, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 4.3845f, POINT_EPSILON);  EXPECT_NEAR(test(3, 1), -0.8479f, POINT_EPSILON); EXPECT_NEAR(test(3, 2), 3.1714, POINT_EPSILON);   EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestTransposeTo)
{
   MatrixF test1(true);
   test1.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test1.mulL(test2);

   MatrixF test(true);

   test1.transposeTo(test);

   EXPECT_NEAR(test(0, 0), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(0, 1), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(0, 2), 0.7081f, POINT_EPSILON);  EXPECT_NEAR(test(0, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(1, 0), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(1, 1), 0.2919f, POINT_EPSILON);  EXPECT_NEAR(test(1, 2), -0.4546f, POINT_EPSILON); EXPECT_NEAR(test(1, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(2, 0), 0.0, POINT_EPSILON);      EXPECT_NEAR(test(2, 1), 0.8415f, POINT_EPSILON);  EXPECT_NEAR(test(2, 2), 0.5403f, POINT_EPSILON);  EXPECT_NEAR(test(2, 3), 0.0f, POINT_EPSILON);
   EXPECT_NEAR(test(3, 0), 4.3845f, POINT_EPSILON);  EXPECT_NEAR(test(3, 1), -0.8479f, POINT_EPSILON); EXPECT_NEAR(test(3, 2), 3.1714, POINT_EPSILON);   EXPECT_NEAR(test(3, 3), 1.0f, POINT_EPSILON);
}

TEST(MatrixTest, TestTransformPlane)
{
   MatrixF test(true);
   test.setPosition(Point3F(5.0f, 2.0f, 1.0f));
   MatrixF test2(EulerF(1.0f, 0.0f, 1.0f));

   test.mulL(test2);

   PlaneF plane(Point3F(0.0f, 0.0f, 0.0f), Point3F(0.0f, 0.0f, 1.0f));

   PlaneF res;
   mTransformPlane(test, Point3F(1.0f, 1.0f, 1.0f), plane, &res);

   EXPECT_NEAR(res.x, 0.0f, POINT_EPSILON);
   EXPECT_NEAR(res.y, 0.8414f, POINT_EPSILON);
   EXPECT_NEAR(res.z, 0.5403f, POINT_EPSILON);
   EXPECT_NEAR(res.d, -1.0f, POINT_EPSILON);

}
