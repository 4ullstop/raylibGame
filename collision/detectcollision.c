#include "detectcollision.h"
#include "collisionplane.h"
#include <stddef.h>
#include <stdio.h>

/*
    This collision detection algorithm was developed according to the document
    Improved Collision Detection and Response by Kasper Faureby which you can find here:
    https://www.peroxide.dk/papers/collision/collision.pdf
*/

Vector3 ConvertVecToEllipsoid(Vector3 r3Vector, Vector3 eRadius)
{
    double eRadX = eRadius.x;
    double eRadY = eRadius.y;
    double eRadZ = eRadius.z;

    double r3X = r3Vector.x;
    double r3Y = r3Vector.y;
    double r3Z = r3Vector.z;

    double Vex = (1 / eRadX) * r3X;
    double Vey = (1 / eRadY) * r3Y;
    double Vez = (1 / eRadZ) * r3Z;

    Vector3 out = {Vex, Vey, Vez};

    return out;
}

void PollCollision(CollisionPacket* collPacket, Mesh* mesh, Vector3 modelLocation)
{
    Vector3 triangle;
    if (mesh->indices != NULL)
    {
        //do we have a mesh with indexed vertices
        for (int i = 0, n = mesh->triangleCount; i < n; i++)
        {
            Vector3 vertex0, vertex1, vertex2;
            GetVertsForIndexedMesh(mesh->vertices, mesh->indices, i, &vertex0, &vertex1, &vertex2);

            vertex0 = Vector3Add(vertex0, modelLocation);
            vertex1 = Vector3Add(vertex1, modelLocation);
            vertex2 = Vector3Add(vertex2, modelLocation);

	    vertex0 = Vector3Divide(vertex0, collPacket->eRadius);
	    vertex1 = Vector3Divide(vertex1, collPacket->eRadius);
	    vertex2 = Vector3Divide(vertex2, collPacket->eRadius);
	    
            CheckTriangle(collPacket, vertex0, vertex1, vertex2);
        }
    }
    else
    {
        //do we have a mesh with non indexed vertices
        for (int i = 0, n = mesh->triangleCount; i < n; i++)
        {
            Vector3 vertex0, vertex1, vertex2;
            GetVertsForNonIndexedMesh(mesh->vertices, i, &vertex0, &vertex1, &vertex2);

            //making sure to add the world space to these verts so that it's translated according to the mesh!
            vertex0 = Vector3Add(vertex0, modelLocation);
            vertex1 = Vector3Add(vertex1, modelLocation);
            vertex2 = Vector3Add(vertex2, modelLocation);

	    
	    vertex0 = Vector3Divide(vertex0, collPacket->eRadius);
	    vertex1 = Vector3Divide(vertex1, collPacket->eRadius);
	    vertex2 = Vector3Divide(vertex2, collPacket->eRadius);
	    
            CheckTriangle(collPacket, vertex0, vertex1, vertex2);
        }
    }
}

void CheckTriangle(CollisionPacket* collPacket, Vector3 p1, Vector3 p2, Vector3 p3)
{
    //constructing the triangle plane to run our calculations on based on the 
    //points of the triangulated mesh
    CPlane plane = {0};
    
    ConstructFromTriangle(&plane, p1, p2, p3);

    if (IsFrontFacingTo(&plane, collPacket->normalizedVelocity))
    {
        //printf("Checking triangles\n");
        double t0, t1;
        bool embededInPlane = false;

        //checking to see if the swept sphere will intersect with the triangle
        double signedDistToTrianglePlane = SignedDistanceToPlane(&plane, collPacket->basePoint);

        //gonna need this a couple of times so cache it
        float normalDotVelocity = Vector3DotProduct(plane.normal, collPacket->velocity);
        
        if (!SetT(normalDotVelocity, signedDistToTrianglePlane, &embededInPlane, &t0, &t1))
        {
            return;
        }

        //Collision is likley to happen, now it's time to run our
        //three test cases for collision wherein our player is going to hit:
        //  Inside of the triangle ||
        //  A triangle edge ||
        //  A triangle vertex

        Vector3 collisionPoint;
        bool foundCollision = false;
        float t = 1.0; //the time at which the collision will occur

        //we'll start with the easy one that doesn't require too much math (inside of the triangle)

        if (!embededInPlane)
        {
            Vector3 planeIntersectionPoint = Vector3Add((Vector3Subtract(collPacket->basePoint, plane.normal)), Vector3Scale(collPacket->velocity, t0));

            if (CheckPointInTriangle(planeIntersectionPoint, p1, p2, p3))
            {
                foundCollision = true;
                t = t0;
                collisionPoint = planeIntersectionPoint;
            }

            //now comes the unfortunate test that results from the intersection
            //point not being inside of the triangle

            /*
                This is what is known as sweeping thet sphere against points and edges of the 
                triangle
            */

            if (foundCollision == false)
            {
                //printf("Not Collision found\n");
                //storing some commonly used terms
                Vector3 velocity = collPacket->velocity;
                Vector3 base = collPacket->basePoint;

                //For each vertex or edge, a quadratic equation will need to be solved
                //So we'll parameterize things to make them more readable

                CheckVertice(velocity, base, &t, p1, &foundCollision, &collisionPoint);
                CheckVertice(velocity, base, &t, p2, &foundCollision, &collisionPoint);
                CheckVertice(velocity, base, &t, p3, &foundCollision, &collisionPoint);

                //now we check against the edges

                //p1 -> p2
                CheckEdge(p1, p2, base, velocity, &t, &foundCollision, &collisionPoint);
                //p2 -> p3
                CheckEdge(p2, p3, base, velocity, &t, &foundCollision, &collisionPoint);
                //p3 -> p1
                CheckEdge(p3, p1, base, velocity, &t, &foundCollision, &collisionPoint);
            }

            if (foundCollision == true)
            {
                //distance to collision 't' is time of collision
                float distToCollision = t * Vector3Length(collPacket->velocity);
                //printf("Collision found\n");

                //Does this triangle qualify for the closest hit?
                //it does if it's the first hit or the closest
                if (collPacket->foundCollision == false || distToCollision < collPacket->nearestDistance)
                {
                    //collision information nessesary for sliding
                    collPacket->nearestDistance = distToCollision;
                    collPacket->intersectionPoint = collisionPoint;
                    collPacket->foundCollision = true;
                }
            }
        }

    }
}



