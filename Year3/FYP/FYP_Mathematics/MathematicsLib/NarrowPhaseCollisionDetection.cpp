#include "stdafx.h"
#include "NarrowPhaseCollisionDetection.h"

#define MAX_ITERATIONS 30

namespace Mathematics
{
	namespace Intersections
	{
		Vector3 NarrowPhaseCollisionDetection::v = Vector3();
		Vector3 NarrowPhaseCollisionDetection::b = Vector3();
		Vector3 NarrowPhaseCollisionDetection::c = Vector3();
		Vector3 NarrowPhaseCollisionDetection::d = Vector3();
		unsigned int NarrowPhaseCollisionDetection::n = 0; //simplex size

		#pragma region CommentedOriginal
		//bool NarrowPhaseCollisionDetection::GJKAlgorithm(const std::vector<Vector3>& aVertices, const std::vector<Vector3>& bVertices)
		//{
		//	Vector3 simplices[3];

		//	Vector3 aPosition = AveragePoint(aVertices);
		//	Vector3 bPosition = AveragePoint(bVertices);

		//	Vector3 difference = aPosition - bPosition;

		//	if ((difference.x == 0.0f) && (difference.y == 0.0f))
		//	{
		//		difference.x = 1.0f;
		//	}

		//	Vector3 a = simplices[0] = SupportPoint(aVertices, bVertices, difference);
		//	Vector3 b;
		//	Vector3 c;
		//	Vector3 aToB;
		//	Vector3 aToC;

		//	if (a.Dot(difference) <= 0)
		//	{
		//		return false;
		//	}

		//	Vector3 dToOrigin = difference.Negate();

		//	int simplex = 0;
		//	int iteration = 0;
		//	while (true)
		//	{
		//		iteration++;

		//		a = simplices[++simplex] = SupportPoint(aVertices, bVertices, dToOrigin);
		//		if (a.Dot(dToOrigin) <= 0)
		//		{
		//			return false;
		//		}

		//		Vector3 aToOrigin = a.Negate();
		//		if (simplex < 2)
		//		{
		//			b = simplices[0];
		//			aToB = b - a;

		//			dToOrigin = TripleProduct(aToB, aToOrigin, aToB);
		//			if (dToOrigin.Magnitude() == 0)
		//			{
		//				// Perpendicular Vector
		//				dToOrigin = dToOrigin.Cross(a);
		//			}
		//			continue;
		//		}

		//		b = simplices[1];
		//		c = simplices[0];

		//		aToB = b - a;
		//		aToC = c - a;

		//		Vector3 acPerp = TripleProduct(aToB, aToC, aToC);
		//		if (acPerp.Dot(aToOrigin) >= 0)
		//		{
		//			dToOrigin = acPerp;
		//		}
		//		else
		//		{
		//			Vector3 abPerp = TripleProduct(aToC, aToB, aToB);
		//			if (abPerp.Dot(aToOrigin) < 0)
		//			{
		//				return true;
		//			}

		//			simplices[0] = simplices[1];
		//			dToOrigin = abPerp;
		//		}
		//		simplices[1] = simplices[2];
		//		--simplex;
		//	}
		//	return false;
		//}

		//Vector3		NarrowPhaseCollisionDetection::AveragePoint(const std::vector<Vector3>& vertices)
		//{
		//	Vector3 averagePoint;

		//	for (int vertex = 0; vertex < vertices.size(); vertex++)
		//	{
		//		averagePoint += vertices[vertex];
		//	}

		//	averagePoint /= vertices.size();

		//	return averagePoint;
		//}
		//Vector3		NarrowPhaseCollisionDetection::SupportPoint(const std::vector<Vector3>& aVertices, const std::vector<Vector3>& bVertices, const Vector3& supportingDirection)
		//{
		//	int i = IndexOfFurthestPoint(aVertices, supportingDirection);
		//	int j = IndexOfFurthestPoint(bVertices, supportingDirection.Negate());

		//	return (aVertices[i] - bVertices[j]);
		//}			
		//Vector3		NarrowPhaseCollisionDetection::TripleProduct(const Vector3& a, const Vector3& b, const Vector3& c)
		//{
		//	return a.Dot(b.Cross(c));
		//}
		//int				NarrowPhaseCollisionDetection::IndexOfFurthestPoint(const std::vector<Vector3>& vertices, const Vector3& supportingDirection)
		//{
		//	int index = 0;
		//	float maxProduct = supportingDirection.Dot(vertices[0]);
		//	for (int vertex = 0; vertex < vertices.size(); vertex++)
		//	{
		//		float dot = supportingDirection.Dot(vertices[vertex]);
		//		if (dot > maxProduct)
		//		{
		//			maxProduct = dot;
		//			index = vertex;
		//		}
		//	}
		//	return index;
		//}
#pragma endregion

		bool NarrowPhaseCollisionDetection::GJKAlgorithm(const std::vector<Vector3>& aVertices, const std::vector<Vector3>& bVertices)
		{
			v = Vector3(1.0f, 0.0f, 0.0f);
			n = 0;

			if (aVertices.size() == 0 || bVertices.size() == 0)
			{
				// No vertices on an object's collider component
				return false;
			}

			c = SupportPoint(aVertices, bVertices, v);

			if (c.Dot(v) < 0)
			{
				return false;
			}
			
			v = v.Negate();
			b = SupportPoint(aVertices, bVertices, v);

			if (b.Dot(v) < 0)
			{
				return false;
			}

			v = TripleProduct(c - b, b.Negate());
			n = 2;

			for (int i = 0; i < MAX_ITERATIONS; i++)
			{
				Vector3 a = SupportPoint(aVertices, bVertices, v);
				if (a.Dot(v) < 0)
				{
					return false;	// No Intersection
				}

				if (NarrowPhaseCollisionDetection::Update(a))
				{
					return true;
				}
			}

			return true;
		}

		bool		NarrowPhaseCollisionDetection::Update(const Vector3& a)
		{
			if (n == 2)	// Triangle handling
			{
				Vector3 ao = a.Negate();
				Vector3 ab = b - a;
				Vector3 ac = c - a;

				Vector3 abc = ab.Cross(ac);

				Vector3 abp = ab.Cross(abc);
				if (abp.Dot(ao) > 0)
				{
					// Origin Lies Outside triangle abc, near line ab
					c = b;
					b = a;
					v = TripleProduct(ab, ao);
					return false;
				}

				Vector3 acp = abc.Cross(ac);
				if (acp.Dot(ao) > 0)
				{
					// Origin near line ac
					b = a;
					v = TripleProduct(ac, ao);
					return false;
				}

				if (abc.Dot(ao) > 0)
				{
					// Origin is above triangle
					d = c; 
					c = b;
					b = a;
					v = abc;
				}
				else
				{
					d = b;
					b = a;
					v = abc.Negate();
				}
				n = 3;
				return false;
			}
			if (n == 3)
			{
				Vector3 ao = a.Negate();
				Vector3 ab = b - a;
				Vector3 ac = c - a;
				Vector3 ad = d - a;

				Vector3 abc = ab.Cross(ac);
				Vector3 acd = ac.Cross(ad);
				Vector3 adb = ad.Cross(ab);

				Vector3 temp;

				const int OVER_ABC = 0x1;
				const int OVER_ACD = 0x2;
				const int OVER_ADB = 0x4;

				int planeTest = (abc.Dot(ao) > 0 ? OVER_ABC : 0) | (acd.Dot(ao) > 0 ? OVER_ACD : 0) | (adb.Dot(ao) > 0 ? OVER_ADB : 0);
				switch (planeTest) 
				{
					case 0:
					{
						//inside the tetrahedron
						return true;
					}
					case OVER_ABC:
					{
						if (!NarrowPhaseCollisionDetection::CheckOneFaceAC(abc, ac, ao)) {
							//in the region of AC
							return false;
						}
						if (!NarrowPhaseCollisionDetection::CheckOneFaceAB(abc, ab, ao)) {
							//in the region of AB
							return false;
						}

						//otherwise, in the region of ABC
						d = c;
						c = b;
						b = a;
						v = abc;
						n = 3;
						return false;
					}
					case OVER_ACD:
					{
						//rotate acd to abc, and perform the same procedure
						b = c;
						c = d;

						ab = ac;
						ac = ad;

						abc = acd;

						if (!NarrowPhaseCollisionDetection::CheckOneFaceAC(abc, ac, ao)) {
							//in the region of AC (actually is ad)
							return false;
						}
						if (!NarrowPhaseCollisionDetection::CheckOneFaceAB(abc, ab, ao)) {
							//in the region of AB (actually is ac)
							return false;
						}

						//otherwise, in the region of "ABC" (which is actually acd)
						d = c;
						c = b;
						b = a;
						v = abc;
						n = 3;
						return false;

					}
					case OVER_ADB:
					{
						//rotate adb to abc, and perform the same procedure
						c = b;
						b = d;

						ac = ab;
						ab = ad;

						abc = adb;
						if (!NarrowPhaseCollisionDetection::CheckOneFaceAC(abc, ac, ao)) {
							//in the region of "AC" (actually is AB)
							return false;
						}
						if (!NarrowPhaseCollisionDetection::CheckOneFaceAB(abc, ab, ao)) {
							//in the region of AB (actually is AD)
							return false;
						}

						//otherwise, in the region of "ABC" (which is actually acd)
						d = c;
						c = b;
						b = a;
						v = abc;
						n = 3;
						return false;
					}
					case OVER_ABC | OVER_ACD:
					{
						if (!NarrowPhaseCollisionDetection::CheckTwoFaces(abc, acd, ac, ab, ad, ao)) {
							if (!NarrowPhaseCollisionDetection::CheckOneFaceAC(abc, ac, ao)) {
								//in the region of "AC" (actually is AB)
								return false;
							}
							if (!NarrowPhaseCollisionDetection::CheckOneFaceAB(abc, ab, ao)) {
								//in the region of AB (actually is AD)
								return false;
							}
							//otherwise, in the region of "ABC" (which is actually acd)
							d = c;
							c = b;
							b = a;
							v = abc;
							n = 3;
							return false;
						}
						else {
							if (!NarrowPhaseCollisionDetection::CheckOneFaceAB(abc, ab, ao)) {
								return false;
							}
							d = c;
							c = b;
							b = a;
							v = abc;
							n = 3;
							return false;
						}
					}
					case OVER_ACD | OVER_ADB:
					{
						//rotate ACD, ADB into ABC, ACD
						temp = b;
						b = c;
						c = d;
						d = temp;

						temp = ab;
						ab = ac;
						ac = ad;
						ad = temp;

						abc = acd;
						acd = adb;
						if (!NarrowPhaseCollisionDetection::CheckTwoFaces(abc, acd, ac, ab, ad, ao)) {
							if (!NarrowPhaseCollisionDetection::CheckOneFaceAC(abc, ac, ao)) {
								//in the region of "AC" (actually is AB)
								return false;
							}
							if (!NarrowPhaseCollisionDetection::CheckOneFaceAB(abc, ab, ao)) {
								//in the region of AB (actually is AD)
								return false;
							}
							//otherwise, in the region of "ABC" (which is actually acd)
							d = c;
							c = b;
							b = a;
							v = abc;
							n = 3;
							return false;
						}
						else {
							if (!NarrowPhaseCollisionDetection::CheckOneFaceAB(abc, ab, ao)) {
								return false;
							}
							d = c;
							c = b;
							b = a;
							v = abc;
							n = 3;
							return false;
						}
					}
					case OVER_ADB | OVER_ABC:
					{
						//rotate ADB, ABC into ABC, ACD
						temp = c;
						c = b;
						b = d;
						d = temp;

						temp = ac;
						ac = ab;
						ab = ad;
						ad = temp;

						acd = abc;
						abc = adb;

						if (!NarrowPhaseCollisionDetection::CheckTwoFaces(abc, acd, ac, ab, ad, ao)) {
							if (!NarrowPhaseCollisionDetection::CheckOneFaceAC(abc, ac, ao)) {
								//in the region of "AC" (actually is AB)
								return false;
							}
							if (!NarrowPhaseCollisionDetection::CheckOneFaceAB(abc, ab, ao)) {
								//in the region of AB (actually is AD)
								return false;
							}
							//otherwise, in the region of "ABC" (which is actually acd)
							d = c;
							c = b;
							b = a;
							v = abc;
							n = 3;
							return false;
						}
						else {
							if (!NarrowPhaseCollisionDetection::CheckOneFaceAB(abc, ab, ao)) {
								return false;
							}
							d = c;
							c = b;
							b = a;
							v = abc;
							n = 3;
							return false;
						}
					}
					default:
						return true;
				}
			}
		}

		bool		NarrowPhaseCollisionDetection::CheckOneFaceAB(const Vector3& abc, const Vector3& ab, const Vector3& ao)
		{
			if (ab.Cross(abc).Dot(ao) > 0)
			{
				//origin in the region of edge ab
				c = b;
				b = ao.Negate();		//b=a
				v = TripleProduct(ab, ao);
				n = 2;

				return false;
			}
			return true;
		}
		bool		NarrowPhaseCollisionDetection::CheckOneFaceAC(const Vector3& abc, const Vector3& ac, const Vector3& ao)
		{
			if (abc.Cross(ac).Dot(ao) > 0) 
			{
				//origin is in the region of edge ac
				b = ao.Negate();	//b=a
				v = TripleProduct(ac, ao);
				n = 2;

				return false;
			}
			return true;
		}
		bool		NarrowPhaseCollisionDetection::CheckTwoFaces(Vector3& abc, Vector3& acd, Vector3& ac, Vector3& ab, Vector3& ad, const Vector3& ao)
		{
			if (abc.Cross(ac).Dot(ao) > 0)
			{
				b = c;
				c = d;
				ab = ac;
				ac = ad;

				abc = acd;
				return false;
			}
			return true;
		}

		Vector3		NarrowPhaseCollisionDetection::AveragePoint(const std::vector<Vector3>& vertices)
		{
			Vector3 averagePoint;

			for (int vertex = 0; vertex < vertices.size(); vertex++)
			{
				averagePoint += vertices[vertex];
			}

			averagePoint /= vertices.size();

			return averagePoint;
		}
		Vector3		NarrowPhaseCollisionDetection::SupportPoint(const std::vector<Vector3>& aVertices, const std::vector<Vector3>& bVertices, const Vector3& supportingDirection)
		{
			int i = IndexOfFurthestPoint(aVertices, supportingDirection);
			int j = IndexOfFurthestPoint(bVertices, supportingDirection.Negate());

			return (aVertices[i] - bVertices[j]);
		}
		Vector3		NarrowPhaseCollisionDetection::TripleProduct(const Vector3& ab, const Vector3& c)
		{
			return ab.Cross(c).Cross(ab);
		}
		int			NarrowPhaseCollisionDetection::IndexOfFurthestPoint(const std::vector<Vector3>& vertices, const Vector3& supportingDirection)
		{
			int index = 0;
			float maxProduct = supportingDirection.Dot(vertices[0]);
			for (int vertex = 0; vertex < vertices.size(); vertex++)
			{
				float dot = supportingDirection.Dot(vertices[vertex]);
				if (dot > maxProduct)
				{
					maxProduct = dot;
					index = vertex;
				}
			}
			return index;
		}
	}
}