class MultasController < ApplicationController
  # GET /multas
  # GET /multas.xml
  def index
    @multas = Multa.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @multas }
    end
  end

  # GET /multas/1
  # GET /multas/1.xml
  def show
    @multa = Multa.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @multa }
    end
  end

  # GET /multas/new
  # GET /multas/new.xml
  def new
    @multa = Multa.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @multa }
    end
  end

  # GET /multas/1/edit
  def edit
    @multa = Multa.find(params[:id])
  end

  # POST /multas
  # POST /multas.xml
  def create
    @multa = Multa.new(params[:multa])

    respond_to do |format|
      if @multa.save
        format.html { redirect_to(@multa, :notice => 'Multa was successfully created.') }
        format.xml  { render :xml => @multa, :status => :created, :location => @multa }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @multa.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /multas/1
  # PUT /multas/1.xml
  def update
    @multa = Multa.find(params[:id])

    respond_to do |format|
      if @multa.update_attributes(params[:multa])
        format.html { redirect_to(@multa, :notice => 'Multa was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @multa.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /multas/1
  # DELETE /multas/1.xml
  def destroy
    @multa = Multa.find(params[:id])
    @multa.destroy

    respond_to do |format|
      format.html { redirect_to(multas_url) }
      format.xml  { head :ok }
    end
  end
end
