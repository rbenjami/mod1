var MOD1;
(function (MOD1)
{
	MOD1.Map = function Map( width, height, scene, points )
	{
		this.indices = [];
		this.width = width;
		this.positions = [];
		this.normals = [];
		this.uvs = [];
		this.ground = new BABYLON.Mesh("Map", scene);

		this.basicGround( width, height, width , height , scene );

		var test = [[40, 25, 20], [20, 10, 70], [30, -10, 70]];
		this.drawMontains(test, width);

		/*
		** Set Vertices
		*/
		this.ground.setVerticesData(this.positions, BABYLON.VertexBuffer.PositionKind, true);
		this.ground.setVerticesData(this.normals, BABYLON.VertexBuffer.NormalKind, true);
		this.ground.setVerticesData(this.uvs, BABYLON.VertexBuffer.UVKind, true);
		this.ground.setIndices(this.indices);
	};

	MOD1.Map.prototype.getAltitude = function( x, y )
	{
		return ( this.positions[this.getCustomIndex( x, y, this.width )] );
	};

	MOD1.Map.prototype.getCustomIndex = function( x, y, width )
	{
		return ( ( x * (width + 1) + y ) * 3 + 1 );
	};

	MOD1.Map.prototype.drawMontains = function( points, width )
	{
		if ( points.length == 0 )
			return ;

		points.sort(function(a, b){ return a[1] - b[1] } );

		for (var i = points.length - 1; i >= 0; i--)
		{
			this.interpolVertex( points[i][0], points[i][2], points[i][1], width, 7 );
		};

		// smooth = 4;
		// for (var i = points.length - 1; i >= 0; i--)
		// {
		// 	index = this.getCustomIndex( points[i][0], points[i][2], width );
		// 	if ( this.positions[index] != points[i][1] )
		// 	{
		// 		this.interpolVertex( points[i][0], points[i][2], points[i][1], width, smooth);
		// 		// i = points.length;
		// 		// smooth--;
		// 	}
		// };

	};

	MOD1.Map.prototype.interpolMap = function( )
	{
		for ( var x = 0; x < this.width; x++ )
		{
			for ( var y = 0; y < this.width; y++ )
			{

			};
		};
	}

	MOD1.Map.prototype.interpolVertex = function( x, y, altitude, width, smooth )
	{
		altitude = altitude < 0 ? altitude + 1 : altitude;
		firstCollision = -1;

		for ( var i = 1; i <= Math.abs( altitude * smooth / 5 ); i++ )
		{
			for ( var j = 0; j <= 360; j+= 0.2 )
			{
				rad = (j * 3.14159) / 180;
				a = Math.ceil( x + i * Math.cos(rad) );
				b = Math.ceil( y + i * Math.sin(rad) );
				if ( a < width && a >= 0 && b < width && b >= 0)
				{
					max_size = 0;
					index = this.getCustomIndex( a, b, width );

					for ( check = 1; check < smooth; check++ )
					{
						tmp_a = Math.ceil( x + i + check * Math.cos(rad) );
						tmp_b = Math.ceil( y + i + check * Math.sin(rad) );
						tmp_index = this.getCustomIndex( a, b, width );
						if ( Math.abs( this.positions[ tmp_index ] ) > Math.abs( max_size ) )
							max_size = this.positions[ tmp_index ];
					}

					newAltitude = (altitude - max_size) * Math.exp( - ( (a - x) * (a - x) ) / Math.abs( altitude * smooth ) - ( (b - y) * (b - y) ) / Math.abs( altitude * smooth ) );
					this.positions[ index ] = newAltitude + max_size;
				}

			};
			firstCollision = firstCollision == 0 ? 1 : firstCollision;
		};
	};

	MOD1.Map.prototype.basicGround = function( width, height, w_subdivisions, h_subdivisions, scene)
	{
		var row, col;

		for (row = 0; row <= h_subdivisions; row++)
		{
			for (col = 0; col <= w_subdivisions; col++)
			{
				var position = new BABYLON.Vector3((col * width) / w_subdivisions - (width / 2.0), 0, ((h_subdivisions - row) * height) / h_subdivisions - (height / 2.0));
				var normal = new BABYLON.Vector3(0, 1.0, 0);

				this.positions.push(position.x, position.y, position.z);
				this.normals.push(normal.x, normal.y, normal.z);
				this.uvs.push(col / w_subdivisions, 1.0 - row / h_subdivisions);
			}
		}

		for (row = 0; row < h_subdivisions; row++)
		{
			for (col = 0; col < w_subdivisions; col++)
			{
				this.indices.push(col + 1 + (row + 1) * (w_subdivisions + 1));
				this.indices.push(col + 1 + row * (w_subdivisions + 1));
				this.indices.push(col + row * (w_subdivisions + 1));

				this.indices.push(col + (row + 1) * (w_subdivisions + 1));
				this.indices.push(col + 1 + (row + 1) * (w_subdivisions + 1));
				this.indices.push(col + row * (w_subdivisions + 1));
			}
		}
	};

})(MOD1 || (MOD1 = {}));